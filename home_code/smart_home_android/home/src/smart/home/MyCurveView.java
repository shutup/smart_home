package smart.home;

import java.util.ArrayList;
import java.util.List;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Style;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

public class MyCurveView extends View
{

    private Paint       p;
    private Paint       p1;
    private List<int[]> coorList;

    private int         width     = 0;
    private int         height    = 0;
    private int         precision = 50;

    public MyCurveView(Context context, AttributeSet attrs)
    {
        super(context, attrs);
        coorList = new ArrayList<int[]>();
        p = new Paint();
        p.setStyle(Style.STROKE);
        p.setStrokeWidth(3);

        p.setColor(Color.RED);
        
        p1=new Paint();
        p1.setColor(Color.BLACK);
    }

    /**
     * 设定折线显示高度
     * 
     * @param h
     */
    public void setHeightView(int h)
    {
        for (int i = 0; i < 20; i++)
        {
            if (i < 19)
            {
                coorList.get(i)[1] = coorList.get(i + 1)[1];
                //Log.d("test", "i am here");
            }
            else
            {
                int top = (int) (height * 0.1);
                float x = height / (float) precision;
                Log.d("test", "top is:"+top);
                if (height - (h * x) > top)
                {
                    coorList.get(i)[1] = (int) (height - (h * x));
                    Log.d("test", "i am here now");
                }
                else
                {
                    coorList.get(i)[1] = top;
                    Log.d("test", "i am here now 2");
                }
            }
        }
    }

    /**
     * 修改精确度
     * 
     * @param pre
     */
    public void setPrecision(int pre)
    {
        this.precision = pre;
    }

    public void setWidthHeight(int w, int h)
    {
        width = this.getWidth();
        Log.d("test", "width:"+width+" ----  height:"+height);
        if (width % 20 == 0)
        {
        	 width = (int)(width / 20);
        }
        else
        {
            width = (int) Math.ceil(width / 20);
        }
        height = (int) (this.getHeight() - this.getHeight() * 0.15);
        Log.d("test", "width:"+width+" ----  height:"+height);
        CoorDinateList();
    }

    private void CoorDinateList()
    {
        for (int i = 0; i < 20; i++)
        {
            int[] coordinate = new int[2];
            coordinate[1] = height;
            if (i < 19)
            {
                coordinate[0] = (i + 1) * (width );
            }
            else
            {
                coordinate[0] = (i) * (width );
            }
            coorList.add(coordinate);
        }
    }

    /**
     * 需要完成重绘时，重写这个方法
     */
    @Override
    protected void onDraw(Canvas canvas)
    {

        super.onDraw(canvas);
        
        canvas.drawText("test", 10,10 , p1);
        canvas.drawLine(10, 10, 10, height+10, p1);
        canvas.drawLine(10,height+10 ,  width*20-10,height+10, p1);
        for (int i = 0; i < coorList.size() - 1; i++)
        {
            canvas.drawLine(coorList.get(i)[0], coorList.get(i)[1], coorList.get(i + 1)[0],
                    coorList.get(i + 1)[1], p);
            //Log.d("test", "repaint");
            //Log.d("test", i+">>>("+coorList.get(i)[0]+","+coorList.get(i)[1]+")--->"+"("+coorList.get(i+1)[0]+","+coorList.get(i+1)[1]+")");
        }
        invalidate();
    }
}
