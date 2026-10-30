# Detection Notes (Blue Team View)

This document describes how the techniques implemented in this repo are
**detected**. It is the most CEH-aligned part of the project: the value of
CEH is understanding both attack and defense.

## MITRE ATT&CK Mapping

| Technique | ID | Where in this repo |
|---|---|---|
| Command and Scripting Interpreter | T1059 | `shell_posix.c`, `shell_win.c` |
| Application Layer Protocol: Web Protocols | T1071.001 | `docs/c2-https.md` |
| Ingress Tool Transfer | T1105 | (if extended to file transfer) |
| Non-Application Layer Protocol | T1095 | Raw TCP mode |

## Network Detection

### Raw TCP Reverse Shell

- **Signature:** outbound TCP connection from a non-standard process to a
  high port on an unknown host.
- **Port heuristics:** listening on :4444, :1337, :9001 — known-default
  reverse-shell ports.
- **Beacon interval:** not applicable (persistent connection).
- **Detection tools:** Zeek, Suricata ET rules, firewall egress logs.

### HTTPS Beaconing

- **Signature:** periodic HTTPS POSTs (fixed interval, similar payload size)
  to a small set of domains, from a process that normally doesn't talk HTTP.
- **JA3/JA3S fingerprinting:** `curl` and `WinHTTP` have distinct JA3
  fingerprints that don't match a browser. Correlate process → TLS.
- **Payload entropy:** if encrypted, high entropy; if JSON, look for keys
  like `cmd`, `output`, `exit_code`.
- **Beacon interval detection:** autocorrelation of inter-request timings;
  fixed intervals are trivial to flag. **Use jitter when testing** (but
  note even jitter is detectable with enough samples).
- **Response size changes:** a response of `{"cmd":null}` vs
  `{"cmd":"whoami"}` is visible in HTTPS inspection logs.

## Host Detection (Linux)

- **Process tree:** `sh` spawned from a binary whose parent isn't `sshd`,
  `login`, or a terminal.
- **`/proc/<pid>/fd`:** socket fd bound to stdin/stdout/stderr — classic.
- **`/proc/<pid>/net/tcp`:** connection to an unknown remote.
- **auditd:** `execve` on `/bin/sh` from a non-standard parent.
- **EDR:** Sysdig, Falco, Wazuh rules for reverse-shell-like process trees.

## Host Detection (Windows)

- **Process ancestry:** `cmd.exe` child of a non-shell, non-service process.
- **`GetExtendedTcpTable`:** established connections from `cmd.exe`.
- **Sysmon Event 3 (network connect):** `cmd.exe` with an outbound
  connection → very high signal.
- **Sysmon Event 1 (process create):** `cmd.exe` with unusual parent.
- **WMI:** process creation events for `cmd.exe` outside normal patterns.
- **Defender / EDR:** most commercial EDR flags `cmd.exe` + outbound
  network as high-risk.

## What This Tool Does NOT Evade

- It does **not** use process injection.
- It does **not** drop persistence.
- It does **not** obfuscate strings (a static scanner will see `/bin/sh`,
  `cmd.exe`, `socket`, `connect`).
- It does **not** bypass Windows Defender or macOS Gatekeeper.
- It does **not** perform domain fronting or CDN abuse.

**This is intentional.** The point of the project is to understand the
primitives, not to build a bypass engine. Adding evasion is a separate
research area and must be done in a lab with explicit approval.

## Blue-Team Exercise

If you want to turn this into a **detection exercise**:

1. Deploy the lab per [`lab-setup.md`](lab-setup.md).
2. Add a **Zeek sensor** to the Host-Only network.
3. Run the shell in each mode.
4. Write Zeek/Suricata rules to detect **your own** traffic.
5. Iterate: add jitter, change ports, change payload framing — and see
   which rules still fire.

This is exactly what "detection engineering" looks like, and it is a
strong portfolio artifact for CEH.