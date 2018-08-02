MarkupNode
===

This is a self-contained markup parser written entirely in C++. It is guaranteed to accept it's own output.

Instructions
---

This is as close to the markup standard as I could get in a single attempt. There are a few differences as a result:

* Everything must be in a single super tag
* Opening tags must not have spaces between the '<' character and the name
* The leaf nodes are stored in a node called "_leaf"
* You'll have to load the files yourself

```C++
Markup markup = "<hello><world>foobar</world></hello>";
string foobar = markup["world"]["_leaf"].ToString();
```

Bugs
---

* Everything must be in a single super tag
* Opening tags must not have spaces between the '<' character and the name
* The leaf nodes are stored in a node called "_leaf"
* It's very slow

Copyright
---

Copyright (c) 2018 Kayne Ruse

This software is provided 'as-is', without any express or implied warranty. In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.