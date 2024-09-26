import matplotlib.pyplot as plt

# 数据
operations = [1000, 6000, 10000, 15000, 20000, 30000]
allocate_times = [0.055505, 0.280284, 0.460486, 0.68207, 0.899471, 1.36591]
resize_times = [0.072805, 0.437016, 0.736293, 1.11601, 1.45565, 2.20643]

# 创建图表
plt.figure(figsize=(10, 6))
plt.plot(operations, allocate_times, marker='o', label='Allocate Time')
plt.plot(operations, resize_times, marker='s', label='Resize Time')

# 添加标题和标签
plt.title('Runtime of Allocate and Resize Operations')
plt.xlabel('Number of Operations')
plt.ylabel('Runtime (seconds)')
plt.legend()

# 显示图表
plt.grid(True)
plt.show()
