#include <gtest/gtest.h>
#include "../lib/bintree.h"

TEST(CreationTestInt,InOrderBST){
  BinSaerchTree<int,inordertraversal> bst;
  bst.insert(5);
  auto it = bst.begin();
  ASSERT_EQ(*it,5);
}


TEST(CreationTestInt,PreOrderBST){
  BinSaerchTree<int,inordertraversal> bst;
  bst.insert(5);
  auto it = bst.begin();
  ASSERT_EQ(*it,5);
}

TEST(CreationTestInt,PostOrderBST){
  BinSaerchTree<int,postordertraversal> bst;
  bst.insert(5);
  auto it = bst.begin();
  ASSERT_EQ(*it,5);
}


TEST(Methods,TrueFind){
  BinSaerchTree<int,inordertraversal> bst1;
  bst1.insert(5);
  bst1.insert(6);
  bst1.insert(7);
  bst1.insert(8);
  auto in_it = bst1.find(7);
  ASSERT_EQ(*in_it,7);
  BinSaerchTree<int,inordertraversal> bst2;
  bst2.insert(5);
  bst2.insert(7);
  bst2.insert(8);
  bst2.insert(9);
  auto pre_it = bst2.find(8);
  ASSERT_EQ(*pre_it,8);
  BinSaerchTree<int,inordertraversal> bst3;
  bst3.insert(5);
  bst3.insert(6);
  bst3.insert(7);
  bst3.insert(8);
  auto post_it = bst3.find(8);
  ASSERT_EQ(*post_it,8);
}

TEST(Methods,FalseFind){
  BinSaerchTree<int,inordertraversal> bst1;
  bst1.insert(5);
  bst1.insert(6);
  bst1.insert(7);
  bst1.insert(8);
  auto in_it = bst1.find(10);
  ASSERT_EQ(in_it,bst1.end());
  BinSaerchTree<int,inordertraversal> bst2;
  bst2.insert(5);
  bst2.insert(7);
  bst2.insert(8);
  bst2.insert(9);
  auto pre_it = bst2.find(10);
  ASSERT_EQ(pre_it,bst2.end());
  BinSaerchTree<int,inordertraversal> bst3;
  bst3.insert(5);
  bst3.insert(6);
  bst3.insert(7);
  bst3.insert(8);
  auto post_it = bst3.find(10);
  ASSERT_EQ(post_it,bst3.end());
}



TEST(Mehtods,Emplace){
  BinSaerchTree<int,inordertraversal> bst;
  bst.insert(100);
  bst.insert(20);
  bst.insert(10);
  bst.insert(30);
  bst.insert(200);
  bst.insert(150);
  bst.insert(300);
  auto it = bst.emplace(87);
  ASSERT_EQ(*it,87);
}

TEST(Mehtods,LowerBound){
  BinSaerchTree<int,inordertraversal> bst;
  bst.insert(100);
  bst.insert(20);
  bst.insert(10);
  bst.insert(30);
  bst.insert(200);
  bst.insert(150);
  bst.insert(300);
  auto it = bst.lower_bound(120);
  ASSERT_EQ(*it,150);
}


TEST(Mehtods,UpperBound){
  BinSaerchTree<int,inordertraversal> bst;
  bst.insert(100);
  bst.insert(20);
  bst.insert(10);
  bst.insert(30);
  bst.insert(200);
  bst.insert(150);
  bst.insert(300);
  auto it = bst.upper_bound(160);
  ASSERT_EQ(*it,200);
}

TEST(Mehtods,Clear){
  BinSaerchTree<int,inordertraversal> bst;
  bst.insert(100);
  bst.insert(20);
  bst.insert(10);
  bst.insert(30);
  bst.insert(200);
  bst.insert(150);
  bst.insert(300);
  bst.clear();
  ASSERT_EQ(bst.size(),0);
}

TEST(Methods,MergeBSTs){
  BinSaerchTree<int,inordertraversal> bst1;
  bst1.insert(100);
  bst1.insert(20);
  bst1.insert(10);
  bst1.insert(30);
  bst1.insert(200);
  bst1.insert(150);
  bst1.insert(300);

  BinSaerchTree<int,inordertraversal> bst2;
  bst2.insert(1);
  bst2.insert(20);
  bst2.insert(3);
  bst2.insert(4);
  bst2.insert(2);
  bst2.insert(150);
  bst2.insert(999);

  bst1.merge(bst2);
  ASSERT_EQ(bst1.size(),11);
}


TEST(EdgeSituatons,Dublicate){
  BinSaerchTree<int,inordertraversal> bst;
  bst.insert(5);
  bst.insert(5);
  ASSERT_EQ(bst.size(),1);
  BinSaerchTree<int,inordertraversal> bst1;
  bst1.insert(5);
  bst1.insert(5);
  ASSERT_EQ(bst1.size(),1);
  BinSaerchTree<int,inordertraversal> bst3;
  bst3.insert(5);
  bst3.insert(5);
  ASSERT_EQ(bst3.size(),1);
}
