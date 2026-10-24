# coff.py moved to tools/coff.py (the gates use it). This loader keeps the research scripts that import it from here
# working without a second copy of the code.
import importlib.util as _util
import os as _os

_spec = _util.spec_from_file_location('_tools_coff', _os.path.join(_os.path.dirname(_os.path.abspath(__file__)), '..', '..', 'coff.py'))
_mod = _util.module_from_spec(_spec)
_spec.loader.exec_module(_mod)
globals().update({k: v for k, v in vars(_mod).items() if not k.startswith('__')})
