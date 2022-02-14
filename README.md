# 42cursus_02_fract-ol

|![image](https://user-images.githubusercontent.com/52701529/153381937-78a7e3ed-ef7d-49cf-aea8-c92ef4e0d66a.png)|![image](https://user-images.githubusercontent.com/52701529/153383091-0b30831c-9bec-4792-9320-5f87267ed538.png)|![image](https://user-images.githubusercontent.com/52701529/153388601-a8a89e00-614f-435d-93a1-f5d9964e73ca.png)|
|----------|--------|--------|
|![image](https://user-images.githubusercontent.com/52701529/153405597-9d8d0421-a24b-4492-ab64-141c9f9417ad.png)|![image](https://user-images.githubusercontent.com/52701529/153405927-b9d11166-8f18-4116-b467-c68fb7fed3f2.png)|![image](https://user-images.githubusercontent.com/52701529/153406020-a92b0486-935f-4575-baea-9791b51d2a8b.png)|
|![image](https://user-images.githubusercontent.com/52701529/153405872-3d45232a-574b-46f2-bcc1-9610f0ea1a89.png)|![image](https://user-images.githubusercontent.com/52701529/153405956-70f6319b-ec2a-40bf-9b34-1cfac0d81518.png)|![image](https://user-images.githubusercontent.com/52701529/153406064-704cb338-0b30-4acd-94ba-183a3962f0e5.png)|

## Fractal이란?

* 자기유사성을 띄는 형태
*  구조가 전체 구조와 비슷한 형태로 끝없이 반복된다

## Fractal의 생성기법

* 시간매개형 - 대개 복소평면 상에서, 각각의 점이 발산하는 속도를 색으로 나타낸 이미지
* 반복함수계 - 규칙적 프랙탈. 기하학적 대체 규칙에 의해 만들어진 도형. 부분과 전체가 완전히 같다
* 무작위적 프랙탈 - 추측 통계학적으로 만들어진 프랙탈

## Mandelbrot set

![image](https://user-images.githubusercontent.com/52701529/153381937-78a7e3ed-ef7d-49cf-aea8-c92ef4e0d66a.png)

* 대표적인 시간매개형 프랙탈. mandelbrot set의 색은 각 점에서의 발산 속도에 따른다
* https://en.wikipedia.org/wiki/Mandelbrot_set
* $Z_{n+1} = {Z_n}^2 + C$

* 수열이 발산하지 않을 복소수 C의 집합으로 정의 된다

## Julia set
![image](https://user-images.githubusercontent.com/52701529/153383091-0b30831c-9bec-4792-9320-5f87267ed538.png)

* julia set도 시간매개형 프랙탈. 각 점에서의 발산 속도에 따라 색이 정해진다
* $Z_{n+1} = {Z_n}^2 + C$
* mandelbrot set의 식과 같다. 다만 다른 점은 복소수 Z의 집합이라는 것
* C값을 임의로 바꾸어 주면 다양한 모습의 julia set을 관찰할 수 있다 https://en.wikipedia.org/wiki/Julia_set#Quadratic_polynomials
* fract-ol에서도 파라미터 값에 따라 julia set을 recompile할 수 있도록 만들라고 나와있다

## Spider set
![image](https://user-images.githubusercontent.com/52701529/153388601-a8a89e00-614f-435d-93a1-f5d9964e73ca.png)

* $Z_{n+1} = {Z_n}^2 + C; C_{n+1} = {C_n\over2} + Z$
* mandelbrot set의 변형
* C 값이 두 번째 계산 부터는 C/2 + Z 로 변경된다
* https://fractview.wordpress.com/2016/03/10/fractint-in-fractview-part-3-the-rest/

## fract-ol 구현 과정

### 주요 알고리즘
* https://en.wikipedia.org/wiki/Mandelbrot_set#Computer_drawings
* 위키피디아의 computer drawings 파트에 수도 코드가 잘 나와있다.
* 각 점마다 while문을 돌며 해당하는 프랙탈 수식에 따라 while문을 탈출할 때의 iter값에 따라 색상을 정한다. (각 점이 발산하는 속도 - 시간매개형 프랙탈)
* $Z_n$의 발산 조건($|Z| > 2$) 외에도 발산 하지 않을 때 적절한 max_iteration값을 통해 탈출 할 수 있게 해야 한다.

### 복소수 처리
* 설명에서 봤듯 fract-ol에서 구현할 프랙탈들은 전부 복소평면상에 나타내야 한다.
* 때문에 복소수 Z, C를 real part, image part로 나누어서 실수상의 계산으로 처리할 수 있게 바꿔준다.
* 복소수 $Z$를 실수부 허수부로 나누어 $(a+bi)$꼴로 생각해보자.
* $(a+bi)^2$ 은 $a^2 + 2abi -b^2$가 된다. 실수부는 $a^2 - b^2$ 허수부는 $2abi$ 가 된다.
* 따라서 복소수 구조체를 하나 만든 다음
```c
tmp = z;
z.r = tmp.r * tmp.r - tmp.i * tmp.i + c.r;
z.i = 2 * tmp.r * tmp.i + c.i;
``` 
* 이런식으로 실수부 허수부 계산을 따로 해주면 된다.

### 색상 처리
* https://stackoverflow.com/questions/16500656/which-color-gradient-is-used-to-color-mandelbrot-in-wikipedia
* while문을 탈출한 iter값에 따라 미리 만들어둔 색상 팔레트값에 대응될 수 있게 했다.

### 확대/축소/이동 (좌표 처리)
* 먼저 screen상의 좌표를 world상의 좌표로 변환하는 방법을 알 필요가 있다.
* mlx hook을 사용하여 마우스 이벤트를 처리할 때 screen상의 x,y좌표값을 받아오게 된다.
* 이를 실제로 내가 처리하고 싶은 world상의 좌표로 계산해 주어야 한다.
* fractal은 복소평면상에 나타낼 것이기 때문에 내가 원하는 (rmin ~ rmax), (imin ~ rmax) 상의 좌표로 바꿔준다.
* arduino의 map함수를 참고하면 쉽다.

```c
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
```

* screen상의 x,y축을 world상의 축 비율에 맞게 바꿔주고 축의 시작점도 이동해준다.

```c
void	screen_to_world(t_point *point, t_cmplx *cmplx, t_frctl *fr)
{
	double	rscale;
	double	iscale;

	rscale = (fr->rmax - fr->rmin) / WIN_W;
	iscale = (fr->imax - fr->imin) / WIN_H;
	cmplx->r = point->x * rscale + fr->rmin;
	cmplx->i = point->y * iscale + fr->imin;
}
```

* 이제 이동을 위해 offset 변수를 하나 추가해 준다. 마우스 이벤트가 일어날 때마다 offx, offy값을 더하고 빼면서 좌표 이동이 일어나게 된다.

```c
void	screen_to_world(t_point *point, t_cmplx *cmplx, t_frctl *fr)
{
	double	rscale;
	double	iscale;

	rscale = (fr->rmax - fr->rmin) / WIN_W;
	iscale = (fr->imax - fr->imin) / WIN_H;
	cmplx->r = (point->x + fr->offx) * rscale + fr->rmin;
	cmplx->i = (point->y + fr->offy) * iscale + fr->imin;
}
```

* 확대를 위해 zoom 변수를 추가해 일정 배율을 곱해주게끔 한다.


```c
void	screen_to_world(t_point *point, t_cmplx *cmplx, t_frctl *fr)
{
	double	rscale;
	double	iscale;

	rscale = (fr->rmax - fr->rmin) / WIN_W;
	iscale = (fr->imax - fr->imin) / WIN_H;
	cmplx->r = (point->x + fr->offx) * rscale * fr->zoom + fr->rmin;
	cmplx->i = (point->y + fr->offy) * iscale * fr->zoom + fr->imin;
}
```

* 여기서 그냥 끝내면 문제가 생긴다. 확대 축소가 마우스 포지션 중심으로 이뤄지지 않는다. 내가 마우스를 올린 지점에서 확대 되거나 축소 돼야 하는데, screen상의 0,0 즉 왼쪽 위 모서리를 기준으로 확대 축소가 이뤄지게 된다. <img src="https://user-images.githubusercontent.com/52701529/153401625-35e0fdbe-04aa-4075-a8b9-c35b0d41aed8.png" width="70%">

* 이를 해결하는 방법은 다음과 같다.
* 확대/축소를 하기 전 마우스가 위치한 world 상의 좌표를 구한다.
* 그 다음 구해둔 world상의 좌표가 확대/축소를 하고 나서 screen상 좌표로 어디에 위치하게 되는지 구한다.(world_to_screen함수 추가 구현)

```c
void	world_to_screen(t_cmplx *cmplx, t_point *point, t_frctl *fr)
{
	double	rscale;
	double	iscale;

	rscale = (fr->rmax - fr->rmin) / WIN_W;
	iscale = (fr->imax - fr->imin) / WIN_H;
	point->x = (cmplx->r - fr->rmin) / fr->zoom / rscale - fr->offx;
	point->y = (cmplx->i - fr->imin) / fr->zoom / iscale - fr->offy;
}
```

* 그 차이를 offset에 빼주면 확대/축소를 하기 전 world상 좌표 그대로 유지할 수 있게 된다.

|![image](https://user-images.githubusercontent.com/52701529/153401956-887d320b-51d7-4608-953f-17ca75b225c3.png)|![image](https://user-images.githubusercontent.com/52701529/153402014-d01d1eae-6b01-414e-88ee-727e1fd8ffdf.png)|
|---|---|

* +추가로 시스템 환경에 따른 차이인건지 내 노트북이 문제인건지 아직 명확히 밝히진 못했지만.. 내 m1 맥북 기준 mlx 마우스 이벤트 처리 때 마우스 클릭이나 이동시 y좌표와 스크롤시 찍히는 y좌표가 반대였다.. 출력할 수 있는 부분은 출력해 가면서 시스템 상의 결과를 잘 확인해보며 테스트 하기..
