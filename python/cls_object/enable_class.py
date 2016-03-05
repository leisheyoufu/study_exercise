class ConsoleInterface():

    @classmethod
    def create_if_enabled(cls, enalbed):
        if enalbed:
            print "create object with class cls()."
            return cls()
        else:
            print "console is disabled."

    def __init__(self):
        print "object init method is called."

    def hello(self):
        #import pdb
        #pdb.set_trace()
        print "hello this is object " + str(id(self))

def main():
    enabled = True
    console = ConsoleInterface.create_if_enabled(enabled)
    console.hello()

if __name__ == "__main__":
    exit(main())
