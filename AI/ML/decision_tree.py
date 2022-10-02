# Load libraries
import pandas as pd
from sklearn.tree import DecisionTreeClassifier # Import Decision Tree Classifier
from sklearn.model_selection import train_test_split # Import train_test_split function
from sklearn import metrics #Import scikit-learn metrics module for accuracy calculation

from sklearn.tree import export_graphviz
#from sklearn.externals.six import StringIO
from six import StringIO
from IPython.display import Image
import pydotplus




col_names = ['outlook', 'temperature', 'humidity',	'wind',	'tennis']
# load dataset
pima = pd.read_csv("dataset - decision_tree.csv", header=None, names=col_names)
print(pima.dtypes)

pima.head()
for col in col_names:
    print(pima[col])
    pima[col] = pima[col].apply(lambda x:float(x.strip()))
    print("done")
print("came")

#split dataset in features and target variable
feature_cols = ['outlook', 'temperature', 'humidity',	'wind']
x = pima[feature_cols] # Features
y = pima.tennis # Target variable

# Create Decision Tree classifer object
clf = DecisionTreeClassifier()

# Train Decision Tree Classifer
clf = clf.fit(x,y)

dot_data = StringIO()
export_graphviz(clf, out_file=dot_data,
                filled=True, rounded=True,
                special_characters=True,feature_names = feature_cols,class_names=['0','1'])
graph = pydotplus.graph_from_dot_data(dot_data.getvalue())
graph.write_png('decision_tree.png')
Image(graph.create_png())
