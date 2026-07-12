### C++20 Modules File Structure Cheat Sheet

| File Type | Core Purpose | Extension | What it starts with |
| :--- | :--- | :--- | :--- |
| **Primary Interface** | Defines the public module API | `.cppm` / `.ixx` | `export module MyModule;` |
| **Interface Partition** | Defines a public part of a module family, (soft-protected) re-exporting it become fully public to the consumers | `.cppm` / `.ixx` | `export module MyModule:Part;` |
| **Internal Partition** | Shared "hard-protected" helper ```across``` module family. | `.cppm` / `.ixx` | `module MyModule:InternalPart;` |
| **Pure Implementation** | Houses heavy function bodies (No exports, still yes to import) | `.cpp` | `module MyModule;` |
