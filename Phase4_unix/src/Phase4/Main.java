package Phase4;
import java.io.File;
import java.io.FileNotFoundException;
import java.nio.file.NotDirectoryException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

	@SuppressWarnings("resource")
	public static void main(String[] args) throws FileNotFoundException, NotDirectoryException {
		File fMasterTransactionFile = new File("master_accounts.txt");
		File fOldMasterAccountsFile = new File("current_accounts.txt");
		
		Scanner scTransaction = new Scanner(fMasterTransactionFile);
		Scanner scAccounts = new Scanner(fOldMasterAccountsFile);
		
		ArrayList<Transaction> arrayOfTransactions = new ArrayList<Transaction>();
		ArrayList<Account> arrayOfAccounts = new ArrayList<Account>();
		
		String transactionString;
		
		Utilities u = new Utilities();
		
		while(scTransaction.hasNextLine()) {
			transactionString = scTransaction.nextLine();
			if(transactionString.length() != 40){
				String culpritFile = u.findFile(transactionString);
				System.err.println("ERROR: Invalid transaction, located in transaction file " + culpritFile + "."
						+ "Transaction: " + transactionString);
			}
			else {
				arrayOfTransactions.add(new Transaction(scTransaction.nextLine()));
			}
			
		}
		
		while(scAccounts.hasNextLine()) {
			arrayOfAccounts.add(new Account(scAccounts.nextLine()));
		}
	}

}
