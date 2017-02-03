# Load Libraries
from nltk import stem
#1. small input to figure out how the three stemmers perform.
input_words = ['movies','dogs','planes','flowers','flies','fries','fry','weeks',
'planted','running','throttle']
#2.Perform lemmatization.
wordnet_lemm = stem.WordNetLemmatizer()
wn_words = [wordnet_lemm.lemmatize(w) for w in input_words]
print wn_words