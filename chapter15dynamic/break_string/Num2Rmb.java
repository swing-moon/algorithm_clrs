import java.util.Arrays;

public class Num2Rmb {
	private String[] hanArr = {"零","壹","贰","叁","肆","伍","陆","柒","捌","玖"};
	private String[] unitArr = {"十","百","千"};

	private String[] divide(double num)
	{
		long zheng = (long)num;
		long xiao = Math.round((num-zheng)*100);
		//Math.round进行四舍五入
		return new String[] {zheng+"", String.valueOf(xiao)};
	}

	private String toHanStr(String numStr)
	{
		String result = "";
		int numLen = numStr.length();

		//依次遍历数字字符串中的每一位数字
		for(int i=0;i<numLen;i++)
		{
			int num = numStr.charAt(i)-48;
			//把char数字转换成int数字，他们的ASCII码值刚好相差48
			//char型数字减去48得到int型数字，例如'4'被转换为4
			if(i==0 && num==0)
			{
				result+="";
				i++;
			}
			else if(i!=numLen-1 && num !=0)
				result+=hanArr[num] + unitArr[numLen-1-i-1];
			    //如果不是最后一位数字，而且数字不是0，则需要添加单位（千，百，十）
			else if(num!=0)
				result+=hanArr[num];
			else
				result+="";
		}
		return result;
	}

	public static void main(String[] args)
	{
		Num2Rmb nr = new Num2Rmb();
		System.out.println(Arrays.toString(nr.divide(236711125.123)));
		System.out.println(nr.toHanStr("4005"));
	}

}
