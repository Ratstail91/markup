# WARNING

This utility is not supported, and does not function correctly. It does not fuction according to the MXL specification.

Markup
===

This is a self-contained markup parser written entirely in C++. It is guaranteed to accept it's own output.

Instructions
---

This is as close to the markup standard as I could get in a single attempt. There are a few differences as a result, see Bugs.

* If no super tag name is given, "markup" will be used as a placeholder
* You'll have to load the files yourself

```C++
Markup markup1("<hello><world>foobar</world></hello>");
string foobar = markup1["world"].GetAttribute(MU_VALUE);

Markup markup2;
markup2 = "<outertag><tag>str</tag></outertag>";
string str = markup2["tag"].GetAttribute(MU_VALUE);
```

Bugs
---

* Everything must be in a single super tag (default is "markup")
* Opening tags must not have spaces between the '<' character and the name
* Parent and child tags must not have the same name
* Sibling tags must not have the same name either
* It's potentially slow due to the "grinding"

Copyright
---

Copyright (c) 2018 Kayne Ruse

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.