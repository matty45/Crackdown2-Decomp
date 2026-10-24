# Changes made to the Crackdown 2 IDB

IDB: `<CD2 dir>\default_patched_vibe.xex.i64` (title-update build only).

## 2026-10-23: function repair and library naming

**Backup taken first:** `Crackdown 2\backup_2026-10-23_before_auto_naming\` holds the `.i64` plus the unpacked `.id0/.id1/.nam/.til` as they were before any change. The database had been left unpacked when an IDA worker was cut off the day before, so the unpacked files are the newest state. To roll back, close IDA and copy all five files back.

1. **Created 21,761 missing functions.** Functions went from 53,005 to 74,766, using jeff's function starts and sizes (`.pdata`, SEH data and control-flow analysis; see `docs/feasibility.md`, section 3).
   - 135 jeff starts fall inside an existing IDA function and were skipped.
   - 12 could not be created.
   - Both lists are in `data/symbols/review_uncreated_functions_2026-10-23.csv` (147 rows).
2. **Applied 14,732 function names** from unique 1:1 exact matches against RuffKing (markers stripped) and Burn:
   - 12,044 RuffKing full-detail matches (instructions with registers and small offsets, ≥6 instructions);
   - 2,518 RuffKing mnemonic-only matches (≥8 instructions, identical length);
   - 311 from Burn.
   Names are the mangled reference names (IDA demangles them for display). Each named function has a function comment `auto-name 2026-10-23: <source> <match type> match`. Nearly all are library code (XDK, Scaleform, Havok, Wwise, Kynapse, CRT). The full list is `data/symbols/auto_names_2026-10-23.csv`.
3. **Existing names were never overwritten.** 141 functions that already had a user-assigned name kept it. Their reference suggestions are in `data/symbols/review_kept_names_2026-10-23.csv` for manual review. Some are placeholders (e.g. `default_0017` → `??0GWaitCondition@@QAA@XZ`); others are descriptive hand names (e.g. `MoppVM_AabbCast_queryRayOnTree__84opcodes` → `hkMoppAabbCastVirtualMachine::queryRayOnTree`).
4. The database was saved after steps 1–3.

## Type import: not completed
- **Attempt 1:** export RuffKing's local types as C declarations (16.7 MB, 43,061 types) and parse them into a temporary type library. This failed: IDA's printed C++ declarations don't round-trip through its parser (templates and `::` scopes), so only 38 types parsed after 17 minutes. Nothing was copied into CD2.
- **Attempt 2:** export RuffKing's types into a binary type library (`Crackdown 2\ruffking_types.til`) to attach to the CD2 database. It was still running very slowly in the RuffKing IDA worker when the session stopped. If the file appears, attach it in IDA via *View → Type libraries → Load* (it never modifies CD2's own local types).
- Meanwhile, `resym` produces full C++ headers straight from the RuffKing PDB (`docs/feasibility.md`, section 7). That is what the decomp workflow needs anyway.
- CD2's own 93 local types were left untouched (the type count is now 94).
- Attempt 2 was abandoned. The RuffKing worker ignored the close request and had to be force-stopped, so no `.til` was written.

## Reference IDBs (RuffKing, Burn): not modified
These sessions only read from them. Both were left unpacked (`.id0/.id1/.nam/.til` beside the `.i64`) because IDA workers were cut off: an MCP disconnect on 2026-10-22, then the forced stop of the stuck RuffKing worker on 2026-10-23. IDA restores from those files on the next open. Since nothing was changed, deleting them and using the packed `.i64` is equivalent. RuffKing's untouched `.i64` (2026-10-18) is also backed up in `RuffKing internal\backup_2026-10-23_before_worker_kill\`.
