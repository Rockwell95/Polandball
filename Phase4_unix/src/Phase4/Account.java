package Phase4;

public class Account {
	public String sAcctNum;
	public String sAcctHolderName;
	
	public char cAcctStatus;
	
	public double dBalance;
	
	public Account(String accountLine) {
		sAcctNum = accountLine.substring(0,5).trim();
		sAcctHolderName = accountLine.substring(6, 26).trim();
		cAcctStatus = accountLine.charAt(27);
		dBalance = Double.parseDouble(accountLine.substring(29));
	}

}
