package Phase4;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

	@SuppressWarnings("resource")
	public static void main(String[] args) throws FileNotFoundException {
		File fMasterTransactionFile = new File("master_accounts.txt");
		File fOldMasterAccountsFile = new File("current_accounts.txt");
		
		Scanner scTransaction = new Scanner(fMasterTransactionFile);
		Scanner scAccounts = new Scanner(fOldMasterAccountsFile);
		
		ArrayList<Transaction> arrayOfTransactions = new ArrayList<Transaction>();
		ArrayList<Account> arrayOfAccounts = new ArrayList<Account>();
		
		Utilities u = new Utilities();
		
		while(scTransaction.hasNextLine()) {
			arrayOfTransactions.add(new Transaction(scTransaction.nextLine()));
		}
		
		while(scAccounts.hasNextLine()) {
			arrayOfAccounts.add(new Account(scAccounts.nextLine()));
		}
	}

}
