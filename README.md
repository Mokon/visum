# VISUM
visum, a financial adviser program
Copyright (C) 2013-2016 David 'Mokon' Bond, All Rights Reserved

## Contributions
To contribute clone and deploy the git hooks:
```bash
git clone https://github.com/Mokon/visum.git
cd visum
./tools/deploy
```
## Contributions
To build the program run
```bash
./tools/build/build
```

Any contributions must follow the existing code style and commit format. This is
documented in ```./docs/style.md```.There exists git hooks to ensure
contributions follow this style. Test cases are required for all new
functionality. Bug fixes MUST include a test that fails before the fix and
passes after.

Contributors are encouraged to mark functionality that is required in a future
commit with a TODO. A TODO comment must follow the format
```// TODO (<taskid>) comment```. At this stage these tasks must also be
documented in ```./TODO.md```. In the future this will be migrated to a proper
 project management system.

## License
The code is currently all right reserved by the author. The intention is to
eventually license under an open source license but it is not ready for that
yet.
