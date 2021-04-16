# 三维空间刚体运动

## 1 旋转矩阵
### 1.1 点、向量和坐标系
**点**和**向量**，三维空间中的某个点的坐标也可以用$\mathbb{R}^3$来描述。假设线性空间的一组基$(e_1,e_2,e_3)$,则向量$a$的坐标为:
$$
a=[e_1,e_2,e_3]
\begin{bmatrix}a_1 \\ a_2 \\ a_3\end{bmatrix}
=a_1 e_1+a_2 e_2 + a_3 e_3.
$$
这里$(a_1,a_2,a_3)^T$称为$a$在此基上的坐标。
对于$a,b \in \mathbb{R}^3$，通常意义下的内积可以写成
$$
a \cdot b=a^Tb=\sum^3_{i=1}a_ib_i=|a||b|cos\left \langle a,b \right\rangle
$$
其中$\left \langle a, b\right \rangle$指向量$a, b$的夹角。
$$
a \times b =
\begin{Vmatrix}
e_1 & e_2 & e_3 \\
a_1 & a_2 & a_3 \\
b_1 & b_2 & b_3 \\
\end{Vmatrix}=
\begin{bmatrix}
    a_2b_3-a_3b_2 \\
    a_3b_1-a_2b_3 \\
    a_1b_2-a_2b_1 
\end{bmatrix}
\begin{bmatrix}
    0 & -a_3 & a_2 \\
    a_3 & 0 & -a_1 \\
    -a_2 & a_1 & 0 \\
\end{bmatrix}b\overset{def}{=}a^\land b
$$
外积的结果是一个向量，它的方向垂直于这两个向量，大小为$|a||b|sin\langle a,b\rangle$,是两个向量张成的四边形的有向面积。
对于外积的运算，可以引入^符号，把$a$写成一个矩阵。即为一个**反对称矩阵**(Skew-symmetric)。
$$
a^\land=\begin{bmatrix}
0 & -a_3 & a_2 \\
a_3 & 0 & -a_1 \\
-a_2 & a_1 & 0
\end{bmatrix}
$$

### 1.2 坐标间的欧式变换

相机视野中某个向量$p$，它在相机坐标系下的坐标为$p_c$，而从世界坐标系下看，它的坐标为$p_w$，那么，这两个坐标之间是如何转换的呢？
两个坐标系间的运动由一个旋转加上一个平移组成，这种运动称为**刚体运动**。相机坐标系到世界坐标系之间，相差了一个**欧式变换(Euclidean Transfrom)**。  
欧式变换由旋转和平移组成。首先考虑旋转。设某个单位正交基$(e_1,e_2,e_3)$经过一次旋转变成了$(e_1^\prime,e_2^\prime,e_3^\prime)$。对于同一个向量$a$,它在两个坐标系下的坐标为$[a_1,a_2,a_3]^T$和$[a_1^\prime,a_2^\prime,a_3^\prime]^T$因为向量本身没变，有
$$
[e_1,e_2,e_3]\begin{bmatrix}
    a_1 \\ a_2 \\ a_3
\end{bmatrix} = [e_1^\prime,e_2^\prime,e_3^\prime]
\begin{bmatrix} a_1^\prime \\ a_2^\prime \\ a_3^\prime \end{bmatrix}
$$
