//Cameron Lim
//CSC 131
//Java program to populate list with names and print a random student name.

//***********************************************************************/

import java.io.*;
import java.util.*;

public class randomStudent
{
    static int index = 0;    
    public static void main(String[] args)
    {
        List<String> names = new ArrayList<String>();
        String again = "yes";
        Scanner input = new Scanner(System.in);

        //Populate the array with names from text file
        try
        {
            File file = new File("nameList.txt");
            BufferedReader br = new BufferedReader(new FileReader(file));

            while(br.readLine() != null)
            {
                names.add(br.readLine());
            }
        } catch(IOException ex)
        {
            System.out.println("File Not Found!");
        }

        //Print random student and loop until no more names are wanted.
        
        while (again.equals("yes") || again.equals("Yes") || again.equals("YES"))
        {
        randomStudent obj = new randomStudent();
        System.out.println();
        System.out.println(obj.getRandomElement(names));
        System.out.println();
        System.out.println("Would you like another name? (If yes, please type YES, yes, or Yes)");
        again = input.nextLine();
        System.out.println();

        }
    }

    //*****************************************************************************************/

   //Returns a random index to get element at that random index.

   static String getRandomElement(List<String> names)
    {
        Random rand = new Random();
        if(!names.isEmpty())
        { 
            index = rand.nextInt(names.size());
        }
            return names.get(index);
    }
}

//************************END******************************************************************/