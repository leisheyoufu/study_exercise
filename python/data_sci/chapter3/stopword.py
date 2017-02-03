from nltk.corpus import stopwords
from nltk.tokenize import word_tokenize
import string
text = "Text mining, also referred to as text data mining, roughly \
equivalent to text analytics,\
refers to the process of deriving high-quality information from text. High-\
quality information is \
typically derived through the devising of patterns and trends through means \
such as statistical \
pattern learning. Text mining usually involves the process of structuring \
the input text \
(usually parsing, along with the addition of some derived linguistic \
features and the removal \
of others, and subsequent insertion into a database), deriving patterns \
within the structured data, \
and finally evaluation and interpretation of the output. 'High quality' in \
text mining usually \
refers to some combination of relevance, novelty, and interestingness. \
Typical text mining tasks \
include text categorization, text clustering, concept/entity extraction, \
production of granular \
taxonomies, sentiment analysis, document summarization, and entity relation \
modeling \
(i.e., learning relations between named entities).Text analysis involves \
information retrieval, \
lexical analysis to study word frequency distributions, pattern \
recognition, tagging/annotation, \
information extraction, data mining techniques including link and \
association analysis, \
visualization, and predictive analytics. The overarching goal is, \
essentially, to turn text \
into data for analysis, via application of natural language processing \
(NLP) and analytical \
methods.A typical application is to scan a set of documents written in a \
natural language and \
either model the document set for predictive classification purposes or \
populate a database \
or search index with the information extracted."

words = word_tokenize(text)
# 2.Let us get the list of stopwords from nltk stopwords english corpus.
stop_words = stopwords.words('english')
print "Number of words = %d"%(len(words))
# 3.    Filter out the stop words.
words = [w for w in words if w not in stop_words]
print "Number of words,without stop words = %d"%(len(words))

words = [w for w in words if w not in string.punctuation]
print "Number of words,without stop words and punctuations = %d"% (len(words))