import datetime
import config.general
import config.helpers

project_github_username="veltzer"
project_name="demos-linux"
project_website=f"https://{project_github_username}.github.io/{project_name}"
project_website_source=f"https://github.com/{project_github_username}/{project_name}"
project_website_git=f"git://github.com/{project_github_username}/{project_name}.git"
project_long_description=f"{project_name} is a project to demo and explore the Linux user space C/C++ API"
project_year_started="2011"
project_description=f"""This project is a source code repository for instructors or expert programmers
who want to explore the Linux C/C++ API.
It has about 1000 examples (as of 1/2020) I found are useful in explaining the Linux API.
The idea is to provide a good coverage of all major features and to resolve disputes
about exactly how a certain API works.

You can find the project at {project_website}

Topics covered by the examples
------------------------------
* Multi-threading
* Multi-processing
* Locking
* Calling system calls without C
* Performance
* Coding in assembly
* Various compiler directives
* Many more...

Platforms supported
-------------------
Only ia64 is supported. I used to support i386 but I don't have a 32 bit
machine anymore. 
Other platforms will be supported if someone is willing to do the work and submit
the patches.

Contributing
------------
This project needs help. fork, commit and request me to pull.
Just open a github account, modify and add examples, commit and ask me to pull...
A lot of the code is documented but some of it is not. More documentation would be welcome.
I would give attribution to whomever contributes.

License
-------
Code is licensed GPL3 and I hold the copyright unless explicity stolen as attributed in the source code.
I encourage people to use this source code as aid for instructing courses.
Please give me some credit if you do wind up using this package and consider dropping
me a note about the fact that you did use the package so I could feel good...

Similar projects
----------------
Michael Kerrisk, the maintainer and author of many of the Linux manual pages has a similar project he calls
TLPI (The Linux Programming Interface) of programs he used in his book of the same title. You can find
it here http://man7.org/tlpi/code/.

Using it
--------
* you need python on your machine:
    try:
        `python --version`
    if python is missing then:
        for deb based distributions (debian, ubuntu, ...) do:
            `sudo apt-get install python`
        for rpm based distributions (fedora, redhat, centos,...) do:
            `sudo yum install python`
* clone the examples: `git clone git@github.com:veltzer/demos-linux.git`
* cd into it: `cd demos-linux`
* install the missing packages and headers needed to compile and run this project `./scripts/ubuntu_install.py`
    Mind you this only works for 15.10 and will install a ton of stuff.
    If you don't want this ton of installations and only want to checkout specific examples
    compile the individual examples as described below.
    if you are on a different Linux distribution try to get as much of these for your platform
    as you can. If you really into contributing I would love a `redhat_install.py` or some such...
    then use `make`
* compiling a specific example
        `make src/examples/performance/cache_misser.elf`
    the name of the elf binary is the same as the example source code with .elf instead of
    .[c|cc].
    You must be at the root of the project to issue the `make` command.
* the most important part: tweak the examples, try to prove me (my comments) wrong, have fun!
"""

project_keywords=[
    "linux",
    "API",
    "C",
    "C++",
    "kernel",
    "userspace",
    "examples",
    "samples",
    "demos",
]

# deb section
deb_package=False

project_data_files = []

codacy_id = None
project_google_analytics_tracking_id = "UA-80940105-1"
project_paypal_donate_button_id = None

project_copyright_years = config.helpers.get_copyright_years(project_year_started)
project_google_analytics_snipplet = config.helpers.get_google_analytics(project_google_analytics_tracking_id)
project_paypal_donate_button_snipplet = config.helpers.get_paypal(project_paypal_donate_button_id)
