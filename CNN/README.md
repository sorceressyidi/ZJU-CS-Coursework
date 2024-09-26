<font face = "Times New Roman">

# MNIST With CNN

This project is a simple implementation of a Convolutional Neural Network (CNN) to classify the MNIST dataset. 

>Implemented based on the coursework of EECS 498-007 / 598-005 Deep Learning for Computer Vision, University of Michigan.

It is divided into two parts:

* **Part 1**: The first part is a simple implementation of a CNN using the PyTorch library. The model is trained on the MNIST dataset and achieves an accuracy of 97.5% `(With Leaky ReLU and Adam Optimizer)` on the test set.

* **Part 2**: The second part is an implementation of a CNN using the **only** **NumPy** library. The model is trained on the MNIST dataset and achieves an accuracy of 92% `(with Adam optimizer) on the test set.`

> **Note**: The model implemented using NumPy is not as efficient as the one implemented using PyTorch because we **only use one convolutional layer** and we use two convolutional layers in the PyTorch model.

### File Organization

The project is organized as follows:

* `HWCNN.ipynb`: This is the Jupyter notebook that contains the implementation of the CNN using PyTorch and **Tested on MNIST dataset with both implementations**.
* `convolutional_networks.py`: This contains the detailed implementation of the CNN using NumPy.

> Note: The MNIST dataset is automatically downloaded when you run the code.



</font>