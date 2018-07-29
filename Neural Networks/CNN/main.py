import keras
from keras.datasets import cifar100
from keras.models import Sequential
from keras.layers import Dense, Dropout, Flatten, Activation
from keras.layers import Conv2D, MaxPooling2D
import numpy

# 100 classes = 100 categories for classification
classes = 100
epochs = 25
batch_size = 32

# image dimensions
image_height, image_width = 32, 32

# load data from CIFAR100 dataset
(x_train, y_train), (x_test, y_test) = cifar100.load_data(label_mode='fine')

# 50000 training images, 10000 test images
x_train = x_train.reshape(50000,image_height,image_width,3)
x_test = x_test.reshape(10000,image_height,image_width,3)

y_train = keras.utils.to_categorical(y_train, classes)
y_test = keras.utils.to_categorical(y_test, classes)

# define model
model = Sequential()

# convolution, pooling and dropout layers
model.add(Conv2D(32, (3, 3), padding='same',input_shape=x_train.shape[1:]))
model.add(Activation('relu'))
model.add(Conv2D(32, (3, 3)))
model.add(Activation('relu'))
model.add(MaxPooling2D(pool_size=(2, 2)))
model.add(Dropout(0.25))

model.add(Conv2D(64, (3, 3), padding='same'))
model.add(Activation('relu'))
model.add(Conv2D(64, (3, 3)))
model.add(Activation('relu'))
model.add(MaxPooling2D(pool_size=(2, 2)))
model.add(Dropout(0.25))

model.add(Flatten())
model.add(Dense(512))
model.add(Activation('relu'))
model.add(Dropout(0.5))
model.add(Dense(classes))
model.add(Activation('softmax'))

# compile model
model.compile(loss=keras.losses.categorical_crossentropy, optimizer=keras.optimizers.Adadelta(),metrics=['accuracy'])

x_train = x_train.astype('float32')
x_test = x_test.astype('float32')
x_train /= 255
x_test /= 255


# train model
model.fit(x_train, y_train, batch_size = batch_size, epochs=epochs, verbose=1, validation_data=(x_test, y_test),shuffle=True)

# test model
score = model.evaluate(x_test, y_test, verbose=1)

print('Final loss: ' + score[0])
print('Final accuracy: ' + score[1])