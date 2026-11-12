import numpy as np

# Исходные данные
X = np.array([[1, 3], [2, 3], [4, 5], [6, 8], [8, 9]]) # Вектор-строка, как в задании (транспонированный)
y1 = np.array([1.17, 2.32, 3.46, 4.13, 4.6])
y2 = np.array([1.83, 2.41, 4.41, 6.83, 8.41])
y3 = np.array([0.86, 0.92, 0.99, 1, 1])

eta = 0.01
w_init = np.array([0.5, 0.5])
batch_size = 2

# --- МОДЕЛЬ 1 ---
print("--- МОДЕЛЬ 1 ---")
w = w_init.copy()
for step in range(5):
    idx = (step * batch_size) % 5 # Индексы для батча
    batch_X = X[idx:idx+batch_size]
    batch_y = y1[idx:idx+batch_size]
    
    # Если батч вышел за пределы массива (например, берем 5-й элемент), корректируем
    if len(batch_X) < batch_size:
        batch_X = np.vstack((batch_X, X[0:batch_size - len(batch_X)]))
        batch_y = np.concatenate((batch_y, y1[0:batch_size - len(batch_y)]))

    grad_w1, grad_w2 = 0, 0
    for i in range(len(batch_X)):
        x1 = batch_X[i, 0]
        # Формула: (y - 4w2*log(x1) + 2w1)^2
        pred = 4 * w[1] * np.log(x1) - 2 * w[0] # Внимание: в задании может быть +2w1, проверьте знак
        error = batch_y[i] - pred
        grad_w1 += 4 * error * 2 # производная по w1
        grad_w2 += 2 * error * (-4 * np.log(x1)) # производная по w2
        
    w[0] -= eta * (grad_w1 / len(batch_X))
    w[1] -= eta * (grad_w2 / len(batch_X))
    print(f"Шаг {step+1}: w1 = {w[0]:.4f}, w2 = {w[1]:.4f}")

# --- МОДЕЛЬ 2 ---
print("\n--- МОДЕЛЬ 2 ---")
w = w_init.copy()
for step in range(5):
    idx = (step * batch_size) % 5
    batch_X = X[idx:idx+batch_size]
    batch_y = y2[idx:idx+batch_size]
    if len(batch_X) < batch_size:
        batch_X = np.vstack((batch_X, X[0:batch_size - len(batch_X)]))
        batch_y = np.concatenate((batch_y, y2[0:batch_size - len(batch_y)]))

    grad = np.zeros(2)
    for i in range(len(batch_X)):
        pred = np.dot(batch_X[i], w)
        error = batch_y[i] - pred
        grad += -2 * error * batch_X[i] # Градиент функции (y - x^T w)^2
        
    w -= eta * (grad / len(batch_X))
    print(f"Шаг {step+1}: w1 = {w[0]:.4f}, w2 = {w[1]:.4f}")

# --- МОДЕЛЬ 3 ---
print("\n--- МОДЕЛЬ 3 ---")
w = w_init.copy()
for step in range(5):
    idx = (step * batch_size) % 5
    batch_X = X[idx:idx+batch_size]
    batch_y = y3[idx:idx+batch_size]
    if len(batch_X) < batch_size:
        batch_X = np.vstack((batch_X, X[0:batch_size - len(batch_X)]))
        batch_y = np.concatenate((batch_y, y3[0:batch_size - len(batch_y)]))

    grad = np.zeros(2)
    for i in range(len(batch_X)):
        z = np.dot(batch_X[i], w)
        sigmoid = 1 / (1 + np.exp(-z))
        error = batch_y[i] - sigmoid
        # Производная сигмоиды: sigmoid * (1 - sigmoid)
        grad += -2 * error * sigmoid * (1 - sigmoid) * batch_X[i]
        
    w -= eta * (grad / len(batch_X))
    print(f"Шаг {step+1}: w1 = {w[0]:.4f}, w2 = {w[1]:.4f}")
