import time
from memory_profiler import memory_usage

start_time = time.time()

def main(n, segments):

    segments = sorted(segments, key=lambda x: x[1])
    points = []
    rightmost = -1

    for segment in segments:
        if segment[0] > rightmost:
            rightmost = segment[1]
            points.append(rightmost)
    
    return points

main(3, [[4, 7], [1, 3], [2, 5], [5, 6]])
# if __name__ == '__main__':
    
#     with open("input.txt", "r") as f, open("output.txt", "w") as out:
#         n = int(f.readline())
#         segments = []
#         for i in range(n):
#             a, b = map(int, f.readline().split())
#             segments.append((a, b))
        
#         res = main(n, segments)

#         out.write(str(len(res)) + "\n")
#         out.write(" ".join(map(str, res)))

    
#     print("Время: ", (time.time() - start_time))
#     print('память: ', memory_usage())
