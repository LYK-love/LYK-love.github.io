---
title: Useful Python Modules
tags:
---





# Scripts

## Clipboard

Copies/Paste text to/from the clipboard.

[pyclip](https://pypi.org/project/pyclip/)

```python
import pyclip

pyclip.copy("hello clipboard") # copy data to the clipboard
cb_data = pyclip.paste() # retrieve clipboard contents 
print(cb_data)  # b'hello clipboard'
cb_text = pyclip.paste(text=True)  # paste as text
print(cb_text)  # 'hello clipboard'

pyclip.clear() # clears the clipboard contents
assert not pyclip.paste()
```

