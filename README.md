# 습하소닉 (프밍 문제 C 풀이)

fromis_9에 'Supersonic'라는 곡이 있다.<br/>
https://www.youtube.com/watch?v=0LiQp7y8Wwc

> Super Super (습하습하)<br/>
Supersonic Supersonic uh (습하 소닉 습하 소닉 하)<br/>
By my side<br/>
Show me right now yeah<br/>
Show me oh Supersonic<br/>
>

프로미스나인은 하이브에 있는 다른 여자아이돌과는 다르게 직접 라이브로 곡을 부르기에 힘들어서 Super를 습하로 발음하고 'Supersonic uh'을 '습하소닉 하'라고 발음한다.

아무튼 은수가 프로미스나인을 너무 좋아하는 바람에 라이브 동영상을 찍어 유튜브에 업로드하려 하는데 요즘에 나온 AI가 해주는 자막을 넣으려고 한다. 근데 위에서 설명한 탓때문인지 아님 그냥 은수가 못찍은것인지, AI가 한두단어는 이상한 말을 써 내린다. 그리하여 문장마다 프로그램이 가사와 비교하여 틀린부분을 찾아내고, 그런 후에 그 부분을 고쳐서 출력하는 프로그램을 만드려고 한다.

## 가사

가사의 범위는 다음과 같다. 문제에서는 다음가사 이외에는 입력되지 않는다.

> 언제든 Day and night<br/>
> Hit me hit me up<br/>
> Hit me hit me up now oh<br/>
>
> 네 맘속 Delight<br/>
> Show me right now yeah<br/>
> Show me right now woo<br/>
>
> Super Super<br/>
> Supersonic Supersonic uh<br/>
> Super Super<br/>
> Supersonic Supersonic uh<br/>
> By my side<br/>
> Show me right now yeah<br/>
> Show me oh Supersonic<br/>
> 
> Heat and sweat 단숨에 후 세게 Blow<br/>
> We got that 이대로 Go with the flow<br/>
> 달라진 온도 차오른 설렘 Overload<br/>
> 자 지금부터 뛰어들어 Ready set you go<br/>

## 입력

첫번째 줄에 AI가 이상하게 써놓은 가사 한줄이 제공된다.

단, 가사는 단어 단위로 최대 2개만 틀린다. 영단어는 영어, 국어단어는 국어로만 제공된다.

## 출력

먼저 고친 단어들이 다음과 같은 형식으로 표시된다.

Supersnic Supersonic um → Supersonic Supersonic uh

* 윈도우에서는 chcp 949을 실행한 후에 한다.

## 예제1

### 입력

```
언제든 Day and neight
```

### 출력

```
neight -> night
언제든 Day and night
```

## 예제2

### 입력

```
Show me rght now yaeh
```

### 출력

```
rght -> right
yaeh -> yeah
Show me right now yeah
```