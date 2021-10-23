# HW-In-The-Loop Test Suite

A collection of hw-in-the-loop tests. Requires `socket-can`.

View test plans [here](https://docs.google.com/document/d/1AHJ6yhIJS4nzz4EUkz22zf57LdoAZyPuRv5f0PJLo0M/edit#heading=h.gjqmn3j6xkwx).

**How to Install and Run on the Rapsberry Pi:**

```bash
cd ~

# ensure dependencies are installed
sudo apt-get install python3
sudo apt-get install python3-pip
sudo apt-get install python3-venv

# clone repository
git clone https://github.com/waterloop/WLoopCAN.git
cd WLoopCAN/hw-in-the-loop-tests

# install dependencies
python3 -m venv env
source ./env/bin/activate
pip3 install -r requirements.txt

# run test script
python3 <testname>.py --interface=can0
```

