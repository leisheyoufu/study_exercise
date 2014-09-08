from pecan import expose, redirect
from webob.exc import status_map
import pecan
from pecan import expose, abort

class BooksController(object):
    @expose()
    def index(self):
        return "Welcome to book section."

    @expose()
    def bestsellers(self):
        return "We have 5 books in the top 10."

class CatalogController(object):
    @expose()
    def index(self):
        return "Welcome to the catalog."

    books = BooksController()

class StudentController(object):
    def __init__(self, student):
        self.student = student

    @expose()
    def name(self):
        return self.student.name

class Student(object):
    def __init__(self,id):
        self.id=id
        self.name= "cl"

def get_student_by_primary_key(primary_key):
    return Student(primary_key)

class RootController(object):

    #@expose(generic=True, template='index.html')
    def index(self):
        return "Welcome to store.example.com!"
    @expose()
    def hours(self):
        return "Open 24/7 on the web."
    @expose(
        template        = None,
        content_type    = 'text/html',
        generic         = False
    )
    def hello(self):
        return 'Hello World'
    @expose()
    def _lookup(self, primary_key, *remainder):
        student = get_student_by_primary_key(primary_key)
        if student:
            return StudentController(student), remainder
        else:
            abort(404)
    @expose()
    def _default(self):
        return 'I cannot say hello in that language'

    @pecan.expose()
    def login(self):
        assert pecan.request.path == '/login'
        username = pecan.request.POST.get('username')
        password = pecan.request.POST.get('password')

        pecan.response.status = 403
        pecan.response.text = 'Bad Login!'

    catalog = CatalogController()


