# Neural Networks

I'm probably going to lift a lot of this from ML by Tom Mitchell

## Characteristics

Generally the problem is formulated this way - 

* The target functionto be learned is defined over instances that can be described by a vector of
predefined features, such as the pixel values. These can be any real value.
* The target function output may be discrete-valued, real-valued, or a vector
of several real- or discrete-valued attributes. 
* The training examples may contain errors or noise.
* Long training times are acceptable.
* Fast evaluation of the learned target function may be required
* Obviously, the target function can be a black box to humans, i.e. its characteristics need not be 
* understood by us.

## Perceptron

NNs can be built on a bunch of different units, perceptron is one of them.  A perceptron takes a 
vector of real-valued inputs, calculates a linear combination of these inputs, then outputs a 1 
if the result is greater than some threshold and -1 otherwise. Consult yellow notebook for more 
details and some mathematical notation.

More precisely, given inputs xl through xn, the output o(x1, . . . , xn) with weights
(w1, . . . , wn) computed by the perceptron is

`o(x1,. ..,xn) =`
* 1 if w0 + w1x1+ w2x2 + ... wnxn > 0
* -1 otherwise
* If you imagine a constant term x0, this is basically the cross product of vectors w and x.
  * ![equation](https://latex.codecogs.com/svg.latex?%7B%5Ccolor%7BGreen%7D%20%5Coverrightarrow%20w%20%5Ccdot%20%5Coverrightarrow%20x%7D)
* General notation of perceptron
  * Page 86 of this book [link](https://www.cin.ufpe.br/~cavmj/Machine%20-%20Learning%20-%20Tom%20Mitchell.pdf)
* So a perceptron basically represents a hyperplane decision surface, and whatever sets can be separated by a hyperplane are called linearly separable sets.
* Can represent AND, OR, NAND and NOR with a single perceptron, but not XOR because its linearly inseparable
* A second layer can represent XOR, with the output of first layer going to 2nd

### Perceptron training rule

One way to learn an acceptable weight vector is to begin with random
weights, then iteratively apply the perceptron to each training example, modifying the perceptron 
weights whenever it misclassifies an example. This process is
repeated, iterating through the training examples as many times as needed until
the perceptron classifies all training examples correctly. Weights are modified at
each step according to the perceptron training rule, which revises the weight wi
associated with input xi according to the rule

wi = wi + dwi

where

dwi = q(t-o)xi

Here t is the target output for the current training example, o is the output generated
by the perceptron, and q is a positive constant called the learning rate. The role
of the learning rate is to moderate the degree to which weights are changed at
each step. It is usually set to some small value (e.g., 0.1) and is sometimes made
to decay as the number of weight-tuning iterations increases.
