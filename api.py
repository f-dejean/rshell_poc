from flask import Flask

api = Flask(__name__)

@api.get("/")
def cmd():
    return "ls\n"

if __name__ == "__main__":
    api.run(port=80)