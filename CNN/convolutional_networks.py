import numpy as np

def softmax_loss(x, y):
    """
    Computes the loss and gradient for softmax classification.
    Inputs:
    - x: Input data, of shape (N, C) where x[i, j] is the score for the jth class for the ith input.
    - y: Vector of labels, of shape (N,) where y[i] is the label for x[i] and 0 <= y[i] < C
    Returns a tuple of:
    - loss: Scalar giving the loss
    - dx: Gradient of the loss with respect to x
    """
    shifted_logits = x - np.max(x, axis=1, keepdims=True) # for numerical stability
    Z = np.exp(shifted_logits).sum(axis=1, keepdims=True) # sum of all classes
    log_probs = shifted_logits - np.log(Z)
    probs = np.exp(log_probs)
    N = x.shape[0]
    loss = (-1.0 / N) * np.sum(log_probs[np.arange(N), y]) # negative log-likelihood
    dx = probs.copy()
    dx[np.arange(N), y] -= 1
    dx /= N
    return loss, dx


class Linear(object):
    @staticmethod
    def forward(x, w, b):
        """
        Computes the forward pass for an linear (fully-connected) layer.
        The input x has shape (N, d_1, ..., d_k) and contains a minibatch of N
        examples, where each example x[i] has shape (d_1, ..., d_k). 
        We will reshape each input into a vector of dimension D = d_1 * ... * d_k, and
        then transform it to an output vector of dimension M.
        
        Inputs:
        - x: shape (N, d_1, ..., d_k)
        - w: shape (D, M)
        - b: shape (M,)
        Returns a tuple of:
        - out: output, of shape (N, M)
        - cache: (x, w, b)
        """
        out = None
        x_reshape = x.reshape(x.shape[0],-1) 
        out = np.dot(x_reshape, w) + b
        cache = (x, w, b)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
        Computes the backward pass for an linear layer.
        Inputs:
        - dout: Upstream derivative, of shape (N, M)
        - cache: Tuple of:
          - x: Input data, of shape (N, d_1, ... d_k)
          - w: Weights, of shape (D, M)
          - b: Biases, of shape (M,)
        Returns a tuple of:
        - dx: Gradient with respect to x, of shape
          (N, d1, ..., d_k)
        - dw: Gradient with respect to w, of shape (D, M)
        - db: Gradient with respect to b, of shape (M,)
        """
        x, w, b = cache
        dx, dw, db = None, None, None

        dx = dout.dot(w.T).reshape(x.shape)
        dw = x.reshape(x.shape[0],-1).T.dot(dout)
        db = dout.sum(axis=0)

        return dx, dw, db


class ReLU(object):

    @staticmethod
    def forward(x):
        """
        Computes the forward pass for a layer of rectified linear units (ReLUs).
        Input:
        - x: Input of any shape
        Returns a tuple of:
        - out: Output of the same shape as x
        - cache: x
        """
        out = None
        out = np.maximum(x, 0)
        cache = x
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
        Computes the backward pass for a layer of rectified
        linear units (ReLUs).
        Input:
        - dout: Upstream derivatives, of any shape
        - cache: Input x, of same shape as dout
        Returns:
        - dx: Gradient with respect to x
        """
        dx, x = None, cache
        dx = (x > 0) * dout
        return dx

class Sigmoid(object):

    @staticmethod
    def forward(x):
        """
        Computes the forward pass for a layer of Sigmoid.
        Input:
        - x: Input of any shape
        Returns a tuple of:
        - out: Output of the same shape as x
        - cache: x
        """
        out = 1 / (1 + np.exp(-x))
        cache = out
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
        Computes the backward pass for a layer of Sigmoid
        Input:
        - dout: Upstream derivatives, of any shape
        - cache: Input x, of same shape as dout
        Returns:
        - dx: Gradient with respect to x
        """
        dx, out = None, cache
        dx = out * (1 - out) * dout
        return dx

class Linear_ReLU(object):

    @staticmethod
    def forward(x, w, b):
        """
        Convenience layer that performs an linear transform
        followed by a ReLU.

        Inputs:
        - x: Input to the linear layer
        - w, b: Weights for the linear layer
        Returns a tuple of:
        - out: Output from the ReLU
        - cache: Object to give to the backward pass
        """
        a, fc_cache = Linear.forward(x, w, b)
        out, relu_cache = ReLU.forward(a)
        cache = (fc_cache, relu_cache)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
        Backward pass for the linear-relu convenience layer
        """
        fc_cache, relu_cache = cache
        da = ReLU.backward(dout, relu_cache)
        dx, dw, db = Linear.backward(da, fc_cache)
        return dx, dw, db

class Linear_Sigmoid(object):

    @staticmethod
    def forward(x, w, b):
        """
        Convenience layer that performs an linear transform
        followed by a Sigmoid.

        Inputs:
        - x: Input to the linear layer
        - w, b: Weights for the linear layer
        Returns a tuple of:
        - out: Output from the Sigmoid
        - cache: Object to give to the backward pass
        """
        a, fc_cache = Linear.forward(x, w, b)
        out, sig_cache = Sigmoid.forward(a)
        cache = (fc_cache, sig_cache)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
        Backward pass for the linear-sig convenience layer
        """
        fc_cache, sig_cache = cache
        da = Sigmoid.backward(dout, sig_cache)
        dx, dw, db = Linear.backward(da, fc_cache)
        return dx, dw, db


class Conv(object):
    @staticmethod
    def forward(x, w, b, conv_param):
        """
        A naive implementation of the forward pass for a convolutional layer.
        The input consists of N data points, each with C channels, height H and
        width W. We convolve each input with F different filters, where each
        filter spans all C channels and has height HH and width WW.

        Input:
        - x: Input data of shape (N, C, H, W)
        - w: Filter weights of shape (F, C, HH, WW)
        - b: Biases, of shape (F,)
        - conv_param: A dictionary with the following keys:
          - 'stride': The number of pixels between adjacent receptive fields
            in the horizontal and vertical directions.
          - 'pad': The number of pixels that is used to zero-pad the input.

        During padding, 'pad' zeros should be placed symmetrically (i.e equally
        on both sides) along the height and width axes of the input. Be careful
        not to modfiy the original input x directly.

        Returns a tuple of:
        - out: Output data of shape (N, F, H', W') where H' and W' are given by
          H' = 1 + (H + 2 * pad - HH) / stride
          W' = 1 + (W + 2 * pad - WW) / stride
        - cache: (x, w, b, conv_param)
        """
        out = None
        pad = conv_param['pad']
        stride = conv_param['stride']
        x_pad = np.pad(x, ((0, 0), (0,0), (pad, pad),(pad, pad)), mode='constant', constant_values=0)
        N,C,H,W = x.shape
        F,C,HH,WW = w.shape

        H_out = 1 + (H + 2 * pad - HH) // stride
        W_out = 1 + (W + 2 * pad - WW) // stride

        out = np.zeros((N, F, H_out, W_out))
        for i in range(N):
            for j in range(F):
                for k in range(H_out):
                    for l in range(W_out):
                      out[i,j,k,l] = np.sum(x_pad[i,:,k*stride:k*stride+HH,l*stride:l*stride+WW]*w[j,:,:,:])

        cache = (x, w, b, conv_param)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
        A naive implementation of the backward pass for a convolutional layer.
          Inputs:
        - dout: Upstream derivatives.
        - cache: A tuple of (x, w, b, conv_param) as in conv_forward_naive

        Returns a tuple of:
        - dx: Gradient with respect to x
        - dw: Gradient with respect to w
        - db: Gradient with respect to b
        """
        dx, dw, db = None, None, None
        x,w,b,conv_param = cache
        pad = conv_param['pad']
        stride = conv_param['stride']

        N,C,H,W = x.shape
        F,C,HH,WW = w.shape
        assert(b.shape == (F,))

        N, F, H_out,W_out = dout.shape
        x_pad = np.pad(x, ((0, 0), (0, 0), (pad, pad), (pad, pad)), mode='constant', constant_values=0)

        dw = np.zeros_like(w)
        db = np.zeros_like(b)
        dx = np.zeros_like(x_pad)

        for i in range(N):
          for j in range(F):
            db[j] += np.sum(dout[i,j,:,:])  #Important
            for k in range(H_out):
              for l in range(W_out):
                dx[i,:,k*stride:k*stride+HH,l*stride:l*stride+WW] += dout[i,j,k,l]*w[j,:,:,:]
                dw[j,:,:,:] += dout[i,j,k,l]*x_pad[i,:,k*stride:k*stride+HH,l*stride:l*stride+WW]
                
        dx = dx[:, :, pad: H+pad, pad: W+pad] # only remain non-padding part        
        # db /= N
        # for j in range(F):
        #   db[j] = np.sum(dout[:,j,:,:])
        return dx, dw, db

class MaxPool(object):

    @staticmethod
    def forward(x, pool_param):
        """
        A naive implementation of the forward pass for a max-pooling layer.

        Inputs:
        - x: Input data, of shape (N, C, H, W)
        - pool_param: dictionary with the following keys:
          - 'pool_height': The height of each pooling region
          - 'pool_width': The width of each pooling region
          - 'stride': The distance between adjacent pooling regions
        No padding is necessary here.

        Returns a tuple of:
        - out: Output of shape (N, C, H', W') where H' and W' are given by
          H' = 1 + (H - pool_height) / stride
          W' = 1 + (W - pool_width) / stride
        - cache: (x, pool_param)
        """
        out = None
        N,C,H,W = x.shape
        pool_height = pool_param['pool_height']
        pool_width = pool_param['pool_width']
        stride = pool_param['stride']
        H_out = 1 + (H - pool_height) // stride
        W_out = 1 + (W - pool_width) // stride
        out = np.zeros((N, C, H_out, W_out))

        for i in range (N):
          for j in range(C):
            for k in range(H_out):
              for l in range(W_out):
                out[i,j,k,l] = np.max(x[i,j,k*stride:k*stride+pool_height,l*stride:l*stride+pool_width])
        cache = (x, pool_param)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
        A naive implementation of the backward pass for a max-pooling layer.
        Inputs:
        - dout: Upstream derivatives
        - cache: A tuple of (x, pool_param) as in the forward pass.
        Returns:
        - dx: Gradient with respect to x
        """
        dx = None
        x, pool_param = cache
        N,C,H,W = x.shape
        pool_height = pool_param['pool_height']
        pool_width = pool_param['pool_width']
        stride = pool_param['stride']
        N,C,H_out,W_out = dout.shape
        dx = np.zeros_like(x)
        
        for i in range(N):
          for j in range(C):
            for k in range(H_out):
              for l in range(W_out):
                x_pool = x[i,j,k*stride:k*stride+pool_height,l*stride:l*stride+pool_width]
                mask = (x_pool == np.max(x_pool))
                dx[i,j,k*stride:k*stride+pool_height,l*stride:l*stride+pool_width] += dout[i,j,k,l]*mask
        return dx


class Conv_ReLU_Pool(object):

    @staticmethod
    def forward(x, w, b, conv_param, pool_param):
        """
        A convenience layer that performs a convolution,
        a ReLU, and a pool.
        Inputs:
        - x: Input to the convolutional layer
        - w, b, conv_param: Weights and parameters for
          the convolutional layer
        - pool_param: Parameters for the pooling layer
        Returns a tuple of:
        - out: Output from the pooling layer
        - cache: Object to give to the backward pass
        """
        a, conv_cache = Conv.forward(x, w, b, conv_param)
        s, relu_cache = ReLU.forward(a)
        out, pool_cache = MaxPool.forward(s, pool_param)
        cache = (conv_cache, relu_cache, pool_cache)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
        Backward pass for the conv-relu-pool
        convenience layer
        """
        conv_cache, relu_cache, pool_cache = cache
        ds = MaxPool.backward(dout, pool_cache)
        da = ReLU.backward(ds, relu_cache)
        dx, dw, db = Conv.backward(da, conv_cache)
        
        return dx, dw, db

class Conv_Sig_Pool(object):

    @staticmethod
    def forward(x, w, b, conv_param, pool_param):
        """
        A convenience layer that performs a convolution,
        a Sigmoid, and a pool.
        Inputs:
        - x: Input to the convolutional layer
        - w, b, conv_param: Weights and parameters for
          the convolutional layer
        - pool_param: Parameters for the pooling layer
        Returns a tuple of:
        - out: Output from the pooling layer
        - cache: Object to give to the backward pass
        """
        a, conv_cache = Conv.forward(x, w, b, conv_param)
        s, sig_cache = Sigmoid.forward(a)
        out, pool_cache = MaxPool.forward(s, pool_param)
        cache = (conv_cache, sig_cache, pool_cache)
        return out, cache

    @staticmethod
    def backward(dout, cache):
        """
        Backward pass for the conv-relu-pool
        convenience layer
        """
        conv_cache, sig_cache, pool_cache = cache
        ds = MaxPool.backward(dout, pool_cache)
        da = Sigmoid.backward(ds, sig_cache)
        dx, dw, db = Conv.backward(da, conv_cache)
        
        return dx, dw, db


class ThreeLayerConvNet(object):
    """
    A three-layer convolutional network with the following architecture:
    conv - relu - 2x2 max pool - linear - relu - linear - softmax
    The network operates on minibatches of data that have shape (N, C, H, W)
    consisting of N images, each with height H and width W and with C input
    channels.
    """

    def __init__(self,
                 input_dims=(1, 28, 28),
                 num_filters=3,
                 filter_size=7,
                 hidden_dim=10,
                 num_classes=10,
                 weight_scale=0.1,
                 reg=0.0):
        """
        Initialize a new network.
        Inputs:
        - input_dims: Tuple (C, H, W) giving size of input data
        - num_filters: Number of filters to use in the convolutional layer
        - filter_size: Width/height of filters to use in convolutional layer
        - hidden_dim: Number of units to use in fully-connected hidden layer
        - num_classes: Number of scores to produce from the final linear layer.
        - weight_scale: Scalar giving standard deviation for random
          initialization of weights.
        - reg: Scalar giving L2 regularization strength
        """
        self.params = {}
        self.reg = reg

        C,H,W = input_dims

        # Initialize weights and biases for the three-layer convolutional network.
        self.params['W1'] = (np.random.randn(num_filters,C,filter_size,filter_size)*weight_scale).astype(np.float64)
        self.params['b1'] = np.zeros(num_filters, dtype=np.float64)
        self.params['W2'] = (np.random.randn(num_filters*H*W//4,hidden_dim)*weight_scale).astype(np.float64)
        self.params['b2'] = np.zeros(hidden_dim, dtype=np.float64)
        self.params['W3'] = (np.random.randn(hidden_dim,num_classes)*weight_scale).astype(np.float64)
        self.params['b3'] = np.zeros(num_classes, dtype=np.float64)

    def save(self, path):
        checkpoint = {
          'reg': self.reg,
          'params': self.params,
        }
        np.save(checkpoint, path)
        print("Saved in {}".format(path))

    def load(self, path):
        checkpoint = np.load(path)
        self.params = checkpoint['params']
        self.reg = checkpoint['reg']
        print("load checkpoint file: {}".format(path))

    def loss(self, X, y=None):
        
        """
        Evaluate loss and gradient for the three-layer convolutional network.
        Input / output: Same API as TwoLayerNet.
        """
        
        X = X
        W1, b1 = self.params['W1'], self.params['b1']
        W2, b2 = self.params['W2'], self.params['b2']
        W3, b3 = self.params['W3'], self.params['b3']

        # pass conv_param to the forward pass for the convolutional layer
        # Padding and stride chosen to preserve the input spatial size
        filter_size = W1.shape[2]
        conv_param = {'stride': 1, 'pad': (filter_size - 1) // 2}

        # pass pool_param to the forward pass for the max-pooling layer
        pool_param = {'pool_height': 2, 'pool_width': 2, 'stride': 2}

        scores = None

        h1,cache1 = Conv_ReLU_Pool.forward(X,W1,b1,conv_param,pool_param)
        h2,cache2 = Linear_ReLU.forward(h1,W2,b2)
        scores,cache3 = Linear.forward(h2,W3,b3)
        

        if y is None:
            return scores

        loss, grads = 0.0, {}

        loss,dout = softmax_loss(scores,y)
        loss += self.reg*(np.sum(W1**2)+np.sum(W2**2)+np.sum(W3**2))
        
        dh2,grads['W3'],grads['b3'] = Linear.backward(dout,cache3)
        #print(dh2,grads['W3'],grads['b3'])
        dh1,grads['W2'],grads['b2'] = Linear_ReLU.backward(dh2,cache2)
        _,grads['W1'],grads['b1'] = Conv_ReLU_Pool.backward(dh1,cache1)

        grads['W3'] += 2*self.reg*W3
        grads['W2'] += 2*self.reg*W2
        grads['W1'] += 2*self.reg*W1
        return loss, grads


class ThreeLayerConvNet_Sig(object):
    """
    A three-layer convolutional network with the following architecture:
    conv - sigmoid - 2x2 max pool - linear - sigmoid - linear - softmax
    The network operates on minibatches of data that have shape (N, C, H, W)
    consisting of N images, each with height H and width W and with C input
    channels.
    """

    def __init__(self,
                 input_dims=(1, 28, 28),
                 num_filters=3,
                 filter_size=7,
                 hidden_dim=10,
                 num_classes=10,
                 weight_scale=0.1,
                 reg=0.0):
        """
        Initialize a new network.
        Inputs:
        - input_dims: Tuple (C, H, W) giving size of input data
        - num_filters: Number of filters to use in the convolutional layer
        - filter_size: Width/height of filters to use in convolutional layer
        - hidden_dim: Number of units to use in fully-connected hidden layer
        - num_classes: Number of scores to produce from the final linear layer.
        - weight_scale: Scalar giving standard deviation for random
          initialization of weights.
        - reg: Scalar giving L2 regularization strength
        """
        self.params = {}
        self.reg = reg

        C,H,W = input_dims

        # Initialize weights and biases for the three-layer convolutional network.
        self.params['W1'] = (np.random.randn(num_filters,C,filter_size,filter_size)*weight_scale).astype(np.float64)
        self.params['b1'] = np.zeros(num_filters, dtype=np.float64)
        self.params['W2'] = (np.random.randn(num_filters*H*W//4,hidden_dim)*weight_scale).astype(np.float64)
        self.params['b2'] = np.zeros(hidden_dim, dtype=np.float64)
        self.params['W3'] = (np.random.randn(hidden_dim,num_classes)*weight_scale).astype(np.float64)
        self.params['b3'] = np.zeros(num_classes, dtype=np.float64)

    def save(self, path):
        checkpoint = {
          'reg': self.reg,
          'params': self.params,
        }
        np.save(checkpoint, path)
        print("Saved in {}".format(path))

    def load(self, path):
        checkpoint = np.load(path)
        self.params = checkpoint['params']
        self.reg = checkpoint['reg']
        print("load checkpoint file: {}".format(path))

    def loss(self, X, y=None):
        
        """
        Evaluate loss and gradient for the three-layer convolutional network.
        Input / output: Same API as TwoLayerNet.
        """
        
        X = X
        W1, b1 = self.params['W1'], self.params['b1']
        W2, b2 = self.params['W2'], self.params['b2']
        W3, b3 = self.params['W3'], self.params['b3']

        # pass conv_param to the forward pass for the convolutional layer
        # Padding and stride chosen to preserve the input spatial size
        filter_size = W1.shape[2]
        conv_param = {'stride': 1, 'pad': (filter_size - 1) // 2}

        # pass pool_param to the forward pass for the max-pooling layer
        pool_param = {'pool_height': 2, 'pool_width': 2, 'stride': 2}

        scores = None

        h1,cache1 = Conv_ReLU_Pool.forward(X,W1,b1,conv_param,pool_param)
        h2,cache2 = Linear_Sigmoid.forward(h1,W2,b2)
        scores,cache3 = Linear.forward(h2,W3,b3)
        

        if y is None:
            return scores

        loss, grads = 0.0, {}

        loss,dout = softmax_loss(scores,y)
        loss += self.reg*(np.sum(W1**2)+np.sum(W2**2)+np.sum(W3**2))
        
        dh2,grads['W3'],grads['b3'] = Linear.backward(dout,cache3)
        #print(dh2,grads['W3'],grads['b3'])
        dh1,grads['W2'],grads['b2'] = Linear_Sigmoid.backward(dh2,cache2)
        _,grads['W1'],grads['b1'] = Conv_ReLU_Pool.backward(dh1,cache1)

        grads['W3'] += 2*self.reg*W3
        grads['W2'] += 2*self.reg*W2
        grads['W1'] += 2*self.reg*W1
        return loss, grads