<%!
    import config.python
%>name: build
on: [push, pull_request]
jobs:
  build:
    name: Build on ${"${{ matrix.container }}"}
    runs-on: ubuntu-latest
    container: ${"${{ matrix.container }}"}
    strategy:
      matrix:
        container: [ 'ubuntu:20.10' ]
        python-version: [3.8]
    steps:
    - uses: actions/checkout@v2
    - name: Set up Python ${"${{ matrix.python-version }}"}
      uses: actions/setup-python@v2
      with:
        python-version: ${"${{ matrix.python-version }}"}
    - name: Upgrade pip
      run: python3 -m pip install --upgrade pip
    - name: Install dependencies
      run: pip3 install -r requirements.txt
    - name: System upgrade
      run: sudo apt-get -y update
    - name: Install OS packages
      run: python -m scripts.install
    - name: Build
      run: make
