import pandas as pd
import numpy as np
from sklearn.preprocessing import MinMaxScaler
from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier
from sklearn.linear_model import LogisticRegression

df = pd.read_csv("german.csv", delimiter="\s+")
german = df.to_numpy(dtype=np.float32)

inputs = german[:, 0:-1]
outputs = german[:, inputs.shape[1]:]

min_max_scaler = MinMaxScaler()

inputs = min_max_scaler.fit_transform(inputs)

x_train, x_test, y_train, y_test = train_test_split(inputs, outputs, test_size=0.4)

kneighbors = KNeighborsClassifier(10, n_jobs=-1).fit(x_train, y_train.ravel())
log_greg = LogisticRegression().fit(x_train, y_train.ravel())

print(f"KNeighbors CCR test: {kneighbors.score(x_test, y_test)*100}%")
print(f"Logistic Regresion CCR test: {log_greg.score(x_test, y_test)*100}%")