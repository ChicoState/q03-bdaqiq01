/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};


// lenght 1
TEST(GuesserTest, SecretTruncation)
{
  Guesser object("zqxwplmnbvtreiughakdjfhgqwertyuiopasdfgh");
  bool guess = object.match("zqxwplmnbvtreiughakdjfhgqwertyu");
  ASSERT_TRUE(guess);
}

//lenght 2
TEST(GuesserTest, longer33Truncation)
{
  Guesser object("abcdefghijklmnopqrstuvwxyz1234567890EXTRA");
  bool guess = object.match("abcdefghijklmnopqrstuvwxyz1234567890E");
  ASSERT_FALSE(guess);
} 
//match 1. 
TEST(GuesserTest, matchingGuess)
{
  Guesser object("Secret");
  bool guess = object.match("Secret"); // 
  ASSERT_TRUE(guess);
}

// match 2. longerguess 
TEST(GuesserTest, LongerGuess)
{
  Guesser object("Secret");
  bool guess = object.match("Secretss"); //does not lock since the ditsnace is 2
  ASSERT_FALSE(guess);
}


// match 3. shorterGuess 
TEST(GuesserTest, shorterGuess)
{
  Guesser object("Secret");
  bool guess = object.match("Secr"); //should not lock since the distance is 2
  ASSERT_FALSE(guess);
}

// match 4. dif character guess 
TEST(GuesserTest, SameLendiffChar)
{
  Guesser object("Secret");
  bool guess = object.match("Secter"); // should not lock
  ASSERT_FALSE(guess);
}


// match 5. emptyGuess 
TEST(GuesserTest, EmptyGuess)
{
  Guesser object("Secret");
  bool guess = object.match("");  // this will lock 
  ASSERT_FALSE(guess);
}

// special objects

//SP 0 

TEST(GuesserTest, EmptySecretWordGuess)
{
  Guesser object("");
  bool guess = object.match("KJHG");  // will lock
  ASSERT_FALSE(guess);
}

// spe 1. emptyobjec
TEST(GuesserTest, EmptySecret)
{
  Guesser object("");
  bool guess = object.match("");
  ASSERT_TRUE(guess);
}


// sp 2. MixedCase object
TEST(GuesserTest, mixedCaseSecret)
{
  Guesser object("aPPLE");
  bool guess = object.match("aPPLE"); 
  ASSERT_TRUE(guess);
}

// sp 3. numbers object
TEST(GuesserTest, numberSecret)
{
  Guesser object("6789");
  bool guess = object.match("6789");
  ASSERT_TRUE(guess);
}

// sp 4. special char object
TEST(GuesserTest, specialCharSecret)
{
  Guesser object("!@%*()");
  bool guess = object.match("!@%*()");
  ASSERT_TRUE(guess);
}

//Sp 5. space character object 
TEST(GuesserTest, spaceCharSecret)
{
  Guesser object("   ");
  bool guess = object.match("   "); 
  ASSERT_TRUE(guess);
}

//Sp 6. space character object 
TEST(GuesserTest, withSpaceSecret)
{
  Guesser object("ab ab");
  bool guess = object.match("ab ab");
  ASSERT_TRUE(guess);
}

//Sp 6. space character object 
TEST(GuesserTest, mixedCahrSecret)
{
  Guesser object("$ab@ab");
  bool guess = object.match("$ab@ab");
  ASSERT_TRUE(guess);
}

//locking 

//1. not locking cause 1 remaing 
TEST(GuesserTest, lastGuess)
{
  Guesser object("aabb");
  bool guess1 = object.match("aaab"); // should not lock
  bool guess2 = object.match("aacb");  //should not lock
  bool guess3 = object.match("aabb"); 
  
  ASSERT_TRUE(guess3);
}

//2. locking cause 0 guesses remaining
TEST(GuesserTest, outOfGuess)
{
  Guesser object("aabb");
  bool guess1 = object.match("aaab"); 
  bool guess2 = object.match("abcb");  
  bool guess3 = object.match("abgb"); 
  bool guess4 = object.match("aabb"); 
  
  ASSERT_FALSE(guess4);
}

//locking due to brute force
TEST(GuesserTest, correctGuessLocked)
{
  Guesser object("aabb");
  bool guess1 = object.match("aabbccd"); //should lock distance is 3
  bool guess2 = object.match("aabb");
  
  ASSERT_FALSE(guess2);
}
//testing distance via match 

//testing remaining
TEST(GuesserTest, zeroGuessLeft)
{
  Guesser object("aabb");
  bool guess1 = object.match("aaab");
  bool guess2 = object.match("abcb");  
  bool guess3 = object.match("abgb"); 
  int rem = object.remaining();
  ASSERT_EQ(0, rem);
}

TEST(GuesserTest, ThreeGuessLeft)
{
  Guesser object("aabb");
  int rem = object.remaining();
  ASSERT_EQ(3, rem);
}

TEST(GuesserTest, OneGuessLeft)
{
  Guesser object("aabb");
  bool guess1 = object.match("abcb"); //should not lock
  bool guess2 = object.match("aacd"); //this should not lock
  int rem = object.remaining();
  ASSERT_EQ(1, rem);
}

TEST(GuesserTest, GuessReset)
{
  Guesser object("abcd");
  object.match("abcf");
  object.match("abcf");
  ASSERT_EQ(1, object.remaining());

  bool correct = object.match("abcd");
  ASSERT_TRUE(correct);
  ASSERT_EQ(3, object.remaining());
}


TEST(GuesserTest, sameGuess)
{
  Guesser object("aabb");
  bool guess1 = object.match("abcb");
  bool guess2 = object.match("abcb");
  int rem = object.remaining();
  ASSERT_EQ(1, rem);
}



