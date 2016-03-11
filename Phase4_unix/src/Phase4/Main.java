package Phase4;
import java.io.File;
import java.io.FileNotFoundException;
import java.nio.file.NotDirectoryException;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

	@SuppressWarnings("resource")
	public static void main(String[] args) throws FileNotFoundException, NotDirectoryException {
		File fMasterTransactionFile = new File(args[0]);
		File fOldMasterAccountsFile = new File(args[1]);
		
		Scanner scTransaction = new Scanner(fMasterTransactionFile);
		Scanner scAccounts = new Scanner(fOldMasterAccountsFile);
		
		ArrayList<Transaction> arrayOfTransactions = new ArrayList<Transaction>();
		ArrayList<Account> arrayOfMasterAccounts = new ArrayList<Account>();
		
		String transactionString;
		String acctString;
		
		boolean transactionSuccess;
		Transaction eofTransaction = new Transaction("00 XXXXXXXXXXXXXXXXXXXX 00000 99999.99 MM");
		
		System.out.println("Welcome to the Bank account system Backend.");
		
		//Read in accounts file
		while(scAccounts.hasNextLine()) {
			acctString = scAccounts.nextLine();
			if(acctString.length() != 44){
				System.err.println("ERROR: Invalid account:" + acctString);
			}
			else{
				arrayOfMasterAccounts.add(new Account(scAccounts.nextLine()));
			}
			
		}
		
		//Read in transactions file
		while(scTransaction.hasNextLine()) {
			transactionString = scTransaction.nextLine();
			if(transactionString.length() != 41){
				String culpritFile = Utilities.findFile(transactionString);
				System.err.println("ERROR: Invalid transaction, located in transaction file " + culpritFile + "."
						+ " Transaction: " + transactionString);
			}
			else {
				arrayOfTransactions.add(new Transaction(scTransaction.nextLine()));
			}	
		}
		
		//Process transactions
		for(Transaction t : arrayOfTransactions){
			transactionSuccess = Utilities.processTransaction(t, arrayOfMasterAccounts);
			if(!transactionSuccess){
				System.err.println("ERROR: Transaction " + t.transAsString() + "has failed.");
			}
		}
		Utilities.processTransaction(eofTransaction, arrayOfMasterAccounts);
	}
}
