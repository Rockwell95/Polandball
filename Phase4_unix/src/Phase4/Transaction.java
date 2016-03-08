package Phase4;

public class Transaction {
	
	public String sTransactionNum;
	public String sAccountHName;
	public String sAccountNumber;
	public String sMiscInfo;
	
	public double dFundsInvolved;
	
	
	
	public Transaction(String transactionRecord) {
		sTransactionNum = transactionRecord.substring(0,2).trim();
		sAccountHName = transactionRecord.substring(3,23).trim();
		sAccountNumber = transactionRecord.substring(24,29).trim();
		
		dFundsInvolved = Double.parseDouble(transactionRecord.substring(30,38));
		sMiscInfo = transactionRecord.substring(39);
	}

}
