from pyconpt import opt

def test_greater():
   num = 101
   assert num > 100

def test_greater_equal():
   num = 100
   assert num >= 100

def test_less():
   num = 100
   assert num < 200

def test_conpt_cartpole():
    cartpole = opt.CartPole()


