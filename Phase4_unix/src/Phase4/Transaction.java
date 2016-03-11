package Phase4;

public class Transaction {
	
	private String sTransactionString;
	private String sTransactionNum;
	private String sAccountHName;
	private String sAccountNumber;
	private String sMiscInfo;
	
	public double dFundsInvolved;
	
	
	
	public Transaction(String transactionRecord) {
		sTransactionString = transactionRecord;
		sTransactionNum = transactionRecord.substring(0,2).trim();
		sAccountHName = transactionRecord.substring(3,23).trim();
		sAccountNumber = transactionRecord.substring(24,29).trim();
		
		dFundsInvolved = Double.parseDouble(transactionRecord.substring(30,38));
		sMiscInfo = transactionRecord.substring(39);
	}
	
	//Transactions are read-only, so these functions return components of the transaction.
	public String getTransactionNumber(){
		return sTransactionNum;
	}
	
	public String getName(){
		return sAccountHName;
	}
	
	public String getAccountNumber(){
		return sAccountNumber;
	}
	
	public String getMisc(){
		return sMiscInfo;
	}
	
	public double getFundsInvolved(){
		return dFundsInvolved;
	}
	
	public String transAsString(){
		return sTransactionString;
	}

}
