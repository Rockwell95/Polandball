package Phase4;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class Main {

	public static void main(String[] args) throws FileNotFoundException {
		File fMasterTransactionFile = new File("master_accounts.txt");
		File fOldMasterAccountsFile = new File("current_accounts.txt");
		
		Scanner scTransaction = new Scanner(fMasterTransactionFile);
		Scanner scAccounts = new Scanner(fOldMasterAccountsFile);
		
	}

}
