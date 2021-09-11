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
    - name: Install OS packages
      run: python -m scripts.install
    - name: Install libffi.so.7
      run: |
        apt install wget
        wget https://mirrors.edge.kernel.org/ubuntu/pool/main/libf/libffi/libffi7_3.3-4_amd64.deb
        dpkg --install libffi7_3.3-4_amd64.deb
    - name: Install dependencies
      run: python -m pip install pymakehelper
#    - name: Upgrade pip
#      run: sudo -H python3 -m pip install --upgrade pip
#    - name: Install dependencies
#      run: python -m pip install -r requirements.txt
    - name: System upgrade
      run: sudo apt-get -y update
    - name: Build
      run: make
