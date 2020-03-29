from simplex import *
import unittest

class Test(unittest.TestCase):
    def test1(self):
        self.assertEqual([0,0,6,7],aux([[1,2],[3,4]],[6,7]))
        self.assertEqual(aux([[1,1,1,1],[2,2,2,2],[3,3,3,3]],[1,2,3]),[0,0,0,0,1,2,3])
        self.assertEqual(aux([[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]], [1,2,3,4]), [0,0,0,0,1,2,3,4])
        self.assertEqual(aux([[1,2,3,4],[3,3,3,3]],[5,6]),[0,0,0,0,5,6])
        
