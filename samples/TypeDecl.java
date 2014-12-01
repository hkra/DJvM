public class TypeDecl {

	public double publicMemberDouble;
	private double privateMemberDouble;
	private double privateMemberInitDouble = 1.0;
	private static double privateStaticMemberDouble;
	private static double privateStaticMemberDoubleInit = 10.0;

	public long publicMemberLong;
	private long privateMemberLong;
	private long privateMemberInitLong = 300;
	private static long privateStaticMemberLong;
	private static long privateStaticMemberLongInit = 3000;

	public static void main(String[] args) {
		double localDouble = 1.0;
		long localLong = 20567890123123098L;
	}
}