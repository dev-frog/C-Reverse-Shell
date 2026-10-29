# Isolated Lab Setup on macOS

This document describes building a **safe, isolated lab** on a macOS host to
develop and test the reverse shell. **Never** run test payloads on your Mac
host, your home network, or any system you don't own.

## Threat Model

Running a reverse shell on a live network is:
1. Illegal against systems you don't own.
2. Likely to trip your ISP's intrusion detection.
3. Likely to trigger endpoint protection on your own machine.
4. Impossible to clean up reliably.

The lab therefore consists of:

- **One hypervisor** (VMware Fusion or VirtualBox).
- **Two or more VMs** on a **Host-Only** network.
- **Snapshots** taken before each test and reverted after.

## 1. Hypervisor Choice

| Option | Notes |
|---|---|
| **VMware Fusion (Personal)** | Free for personal use on Apple Silicon + Intel. Best snapshot UI. Recommended. |
| **VirtualBox** | Free. Works on Apple Silicon (with caveats). Slightly slower. |
| **UTM** | Apple Silicon alternative based on QEMU. Works but fiddly. |
| **Parallels** | Paid. Very fast. Good if you already own it. |

## 2. VM Images

Download **clean** images only from official sources:

| Role | Suggested image | Download |
|---|---|---|
| Linux target | Ubuntu Server 22.04 LTS ISO | https://ubuntu.com/download/server |
| Windows target | Windows 11 Enterprise Evaluation (90-day) | https://www.microsoft.com/en-us/evalcenter/ |
| Attacker | Kali Linux (official) | https://www.kali.org/get-kali/ |

> 💡 Windows eval ISOs expire but are legal and free. Use them. Do not use
> pirated Windows ISOs — that's a *different* illegal thing.

## 3. Network Configuration (Critical)

Set **every** VM's network adapter to **Host-Only**:

- **VMware Fusion:** VM → Settings → Network Adapter → *Private to my Mac*.
- **VirtualBox:** Settings → Network → Attached to: *Host-only Adapter*.

**Never** use:

- **Bridged** — VM is on your real LAN.
- **NAT** — VM can reach the internet via your Mac.

**Why:** Host-Only means VMs can talk to each other and to your Mac, but
**cannot reach the internet** or your home router's other devices. Even if
a payload behaves badly, it can't reach anything real.

## 4. Snapshot Discipline

**Before running any test:**

```bash
# (UI) Take a snapshot named "clean"
```

Never reuse a "dirty" VM for a new test. Your shell might have made files,
modified configs, or even installed persistence — snapshot reversion is the
only reliable cleanup.

## 5. Verify Isolation

From inside each VM, run:

```bash
ping 8.8.8.8
```

This must fail (or time out). If it succeeds, your network is NOT
isolated — fix the adapter setting before continuing.
