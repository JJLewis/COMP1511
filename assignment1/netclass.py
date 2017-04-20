import numpy as np
import openpbm
import math

class NeuralNet():

    def printLine(self):
        print "--------------------"

    def pMatrixDim(self, m1, n1, m2, n2):
        self.printLine()
        print n1 + " width: " + str(len(m1[0]))
        print n1 + " height: " + str(len(m1))

        print n2 + " width: " + str(len(m2[0]))
        print n2 + " height: " + str(len(m2))
        self.printLine()

    def makeGuess(self, input):
        # layers
        '''
        l0 = input
        l1 = self.nonlin(np.dot(l0, self.syn0))
        l2 = self.nonlin(np.dot(l1, self.syn1))
        l3 = self.nonlin(np.dot(l2, self.syn2))
        
        return l3.tolist()
        '''
        layers = self.genLayersFrom(input, self.syns)
        return layers[len(layers) - 1].tolist()

    # sigmoid function
    def nonlin(self, x, deriv=False):
        if deriv:
            return x * (1 - x)
        return 1 / (1 + np.exp(-x))

    def flattenPixels(self, pixels):
        all = []
        for i in xrange(len(pixels)):
            all += pixels[i]
        return all

    def expectedOutputFor(self, n):
        arr = [0] * 10
        arr[n] = 1
        return arr

    def loadTrainingData(self, fstruct, numnum, maxPerNum):
        training = []
        expected = []
        for n in xrange(numnum):
            tempExpected = self.expectedOutputFor(n)
            for f in xrange(maxPerNum + 1):
                file = openpbm.fileNameFrom(fstruct, n, f)
                pixels = openpbm.read_pbm(file)
                flat = self.flattenPixels(pixels)
                training.append(flat)
                expected.append(tempExpected)
        return (np.array(training), np.array(expected))

    def train(self, numtimes, training, expected):
        for t in xrange(numtimes):
            # layers
            '''
            l0 = training
            l1 = self.nonlin(np.dot(l0, self.syn0))
            l2 = self.nonlin(np.dot(l1, self.syn1))
            l3 = self.nonlin(np.dot(l2, self.syn2))
            '''
            layers = self.genLayersFrom(training, self.syns)
            #self.printDimensionOf(layers)

            # backpropagation
            last_error = expected - layers[len(layers) - 1]

            error = 'Error: ' + str(np.mean(np.abs(last_error)))
            if t >= 10:
               if (t % (numtimes / 10)) == 0:
                  print error
            else:
                print error

            # calculate deltas
            '''
            l3_delta = l3_error * self.nonlin(l3, deriv=True)
            l2_error = l3_delta.dot(self.syn2.T)
            l2_delta = l2_error * self.nonlin(l2, deriv=True)
            l1_error = l2_delta.dot(self.syn1.T)
            l1_delta = l1_error * self.nonlin(l1, deriv=True)
            '''
            deltasAndErrors = self.genDeltasAndErrors(last_error, layers, self.syns)

            # update synapses
            '''
            self.syn2 += l2.T.dot(l3_delta)
            self.syn1 += l1.T.dot(l2_delta)
            self.syn0 += l0.T.dot(l1_delta)
            '''
            self.syns = self.updateSynapses(layers, self.syns, deltasAndErrors)

    def printDimensionOf(self, obj):
        for i in xrange(len(obj)):
            a = obj[i]
            print str(len(a[0])) + " x " + str(len(a))

    def updateSynapses(self, layers, syns, deltasAndErrors):
        newSyns = syns
        for i in xrange(len(deltasAndErrors)):
            newSyns[i] += layers[i].T.dot(deltasAndErrors[i][1])
        return newSyns

    def invertArray(self, arr):
        num = len(arr)
        new = []
        for i in xrange(num):
            new.append(arr[num - i - 1])
        return new


    def genDeltasAndErrors(self, initialError, layers, syns):
        top = len(layers) - 1
        counter = top - 1

        deltasAndErrors = [[initialError, initialError * self.nonlin(layers[top], deriv=True)]]
        while counter > 0:
            prevDelta = deltasAndErrors[top - counter - 1][1]
            nextError = prevDelta.dot(syns[counter].T)
            nextDelta = nextError * self.nonlin(layers[counter], deriv=True)
            deltasAndErrors.append([nextError, nextDelta])
            counter -= 1
        return self.invertArray(deltasAndErrors)

    def genLayersFrom(self, training, syns):
        layers = []
        for i in xrange(len(syns) + 1):
            layers.append(training if i == 0 else self.nonlin(np.dot(layers[i-1], syns[i-1])))
        return layers

    def genSyn(self, inputs, outputs):
        return 2 * np.random.random((inputs, outputs)) - 1

    def numSynForLayer(self, numInput, num):
        return int(math.ceil(numInput * ((3.0 / 4.0) ** num)))

    def initSyns(self, numInput, numOutput, numLayers):
        syns = []
        for i in xrange(numLayers):
            thisOut = self.numSynForLayer(numInput, i + 1)
            syn = []
            if i == 0:
                syn = self.genSyn(numInput, thisOut)
            else:
                prevOut = self.numSynForLayer(numInput, i)
                numOut = thisOut
                if i + 1 == numLayers:
                    numOut = numOutput
                syn = self.genSyn(prevOut, numOut)
            syns.append(syn)
        return syns

    def __init__(self, numLayers, numInput, numOutputNodes):
        np.random.seed(1)

        '''
        nodesInL1 = int(math.ceil(((2/3) * numInput) + numOutputNodes))
        #nodesInL1 = numInput

        self.syn0 = 2 * np.random.random((numInput, nodesInL1)) - 1
        self.syn1 = 2 * np.random.random((nodesInL1, int(math.ceil(nodesInL1/2)))) - 1
        self.syn2 = 2 * np.random.random((int(math.ceil(nodesInL1/2)), numOutputNodes)) - 1
        '''

        self.syns = self.initSyns(numInput, numOutputNodes, numLayers)