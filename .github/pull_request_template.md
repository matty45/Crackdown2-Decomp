## What this changes

<!-- Which source file(s) and functions (addresses). Matched by hand or with an agent (which one)? -->

## Verification

<!-- Paste the last lines of `py -I tools\cd2.py verify`. Maintainers re-run it; this is for the record. -->

```
```

## Checklist

- [ ] `py -I tools\cd2.py verify` passes.
- [ ] New exact functions are added to `config/matched_functions.json` (address, size, mangled symbol prefix;
      `"ltcg": true` if exact only under `--ltcg`).
- [ ] Nothing changed under `tools/`, `tests/` or `.github/` (or a maintainer agreed).
- [ ] Anything non-obvious learned is in `docs/matching-notes.md`.
- [ ] No binaries, no data or code from the game, no machine-specific paths.
