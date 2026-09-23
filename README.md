<img src="image/lumini_banner.gif">

Lumini is a minimalist, safe, procedural programming language designed for both rapid high-level scripting along low-level development. It focuses heavily on delivering rapid speed, strong security, and zero-overhead abstractions.

## Syntax Example
```
import std
fn main():
	std.println("Hello World!")
end
```

## Key Goals
* **C/C++ compatibility**
* **cross platform code**
* **modern syntax & features**

	### Feature Goals:
    * **Modern Features:** Native support for modules and zero overhead objects.
    * **Minimalist Design:** Enforces a strict constraint of under 40 total keywords to ensure simplicity and maintainability.
    * **Platform Independence:** Utilizes LuminiVM for seamless cross-platform execution.
    * **Blazing-Fast Production:** Employs the Lumini Compiler to generate optimized, platform-specific machine code.
    * **AOT Compilation Backend:** Leverages libgccjit for high-performance Ahead-Of-Time code generation.


## Roadmap
* [x] Initial Stages
* [ ] Lumini VM
	* [x] Lumini VM Architecture
	* [x] ABI & Functinalities
	* [ ] Runtime   
* [ ] Lumini Language Standard & Compiler
* [ ] Lumini Shell
* [ ] First Release

## Getting Started
* 
	### Requierments
    * **C Compiler**: `gcc 14+` or `clang 18+`
    * **Build System**: `make 4.4+`
    * **shell**: `bash`

## Contirbuting
Contributions are always welcome. Help shape the core architecture of Lumini! 

Whether you are fixing a bug, optimization profiling, or improving documentation, 

your help is highly appreciated.

## License

* **Source Code:** This project is licensed under the [Apache 2.0 License](http://www.apache.org/licenses/LICENSE-2.0) - see the [License](LICENSE) file for details.
* **Branding & Graphics:** All assets within the `image/` directory are strictly protected under the [Creative Commons Attribution-NoDerivatives 4.0 International](images/LICENSE) license (see [image/license](image/LICENSE)). No modifications or derivatives of visual assets are permitted.