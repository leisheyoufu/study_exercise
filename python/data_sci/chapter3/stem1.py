from nltk import stem
#1. small input to figure out how the three stemmers perform.
input_words = ['movies','dogs','planes','flowers','flies','fries','fry','weeks','planted'
,'running','throttle']
# Let’s jump into the different stemming algorithms, as follows:
#2.Porter Stemming
porter = stem.porter.PorterStemmer()
p_words = [porter.stem(w) for w in input_words]
print p_words
#3.Lancaster Stemming
lancaster = stem.lancaster.LancasterStemmer()
l_words = [lancaster.stem(w) for w in input_words]
print l_words
#4.Snowball stemming
snowball = stem.snowball.EnglishStemmer()
s_words = [snowball.stem(w) for w in input_words]
print s_words
wordnet_lemm = stem.WordNetLemmatizer()
wn_words = [wordnet_lemm.lemmatize(w) for w in input_words]
print wn_words