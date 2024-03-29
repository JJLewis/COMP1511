import numpy as np

# sigmoid function
def nonlin(x, deriv=False):
    if deriv:
        return x*(1-x)
    return 1/(1+np.exp(-x))

# input data
x = np.array([
    [0,0,1],
    [0,1,1],
    [1,0,1],
    [1,1,1]
])

y = np.array([
    [0,0],
    [1,0],
    [1,1],
    [0,1]
])

print x
print y

# seed
np.random.seed(1)

# synapses
syn0 = 2 * np.random.random((3,4)) - 1
syn1 = 2 * np.random.random((4,2)) - 1

print syn0
print syn1

# training
for j in xrange(60000):

    # layers
    l0 = x
    l1 = nonlin(np.dot(l0, syn0))
    l2 = nonlin(np.dot(l1, syn1))

    # backpropagation
    l2_error = y - l2
    if (j % 10000) == 0:
        print 'Error: ' + str(np.mean(np.abs(l2_error)))

    # calculate deltas
    l2_delta = l2_error * nonlin(l2, deriv=True)
    l1_error = l2_delta.dot(syn1.T)
    l1_delta = l1_error * nonlin(l1, deriv=True)

    # update synapses
    syn1 += l1.T.dot(l2_delta)
    syn0 += l0.T.dot(l1_delta)
    if j == 0:
        print syn1.shape
        print l1.T.shape
        print l2_delta.shape
        print syn0.shape
        print l0.T.shape
        print l1_delta.shape

print 'output after training'
print l2
print syn0
print syn1

print 'output after changed input'
x = np.array([
    [0,1,1]
])

# layers
l0 = x
l1 = nonlin(np.dot(l0, syn0))
l2 = nonlin(np.dot(l1, syn1))

print l2