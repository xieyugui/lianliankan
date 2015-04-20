/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lianliankanx.R;
import android.app.Activity;
import android.content.Intent;
import android.content.pm.ApplicationInfo;
import android.content.pm.PackageManager;
import android.os.Bundle;
import android.text.TextUtils;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.LinearLayout;

import com.unionsy.sdk.OnExitScreenListener;
import com.unionsy.sdk.OnGetAdsSizeListener;
import com.unionsy.sdk.OnSsjjAdsListener;
import com.unionsy.sdk.SsjjAdsManager;
import com.unionsy.sdk.SsjjAdsSize;
import com.unionsy.sdk.SsjjAdsView;
import com.unionsy.sdk.SsjjExitScreenManager;
import com.unionsy.sdk.SsjjFullScreenManager;
import com.unionsy.sdk.SsjjPauseScreenManager;

public class AppActivity extends Activity implements OnClickListener{
	private static final String TAG = "Ads_SDK_Demo_Main";

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);   
		//setContentView(R.layout.activity_main);
		bannerLayout = (LinearLayout) findViewById(R.id.layout_add_banner);// demo中为按钮"添加banner广告"的事件载体
		
		//findViewById(R.id.btn_show_banner).setOnClickListener(this);       //按钮：添加 Banner 广告 
		//findViewById(R.id.btn_show_pause_screen).setOnClickListener(this); //按钮：显示 插屏 广告
		//findViewById(R.id.btn_show_full_screen).setOnClickListener(this);  //按钮：显示 全屏 广告
		//findViewById(R.id.btn_clear_cache).setOnClickListener(this);       //按钮：清除广告缓存
		
		//updataTitle(); // 测试使用,顶部的title,方便测试看版本和Key
		
		// 请确保已经在AndroidManifest.xml文件中进行了相关配置，若还没有可参看本demo中的AndroidManifest.xml文件
		
		//在onCreate方法中调用SDK初始化参数，请传入Activity实例对象
		SsjjAdsManager.init(AppActivity.this); 
	}
	
	
	@Override
	protected void onStart() {
		super.onStart();
		
		showBanner(); // Banner广告相关方法
		SsjjPauseScreenManager.preLoad(AppActivity.this); // 预加载 插屏 广告
		SsjjExitScreenManager.preLoad(AppActivity.this);  // 预加载 退出插屏广告
		SsjjFullScreenManager.preLoad(AppActivity.this);  // 预加载 全屏 广告
	}


	@Override
	public void onBackPressed() {
		// 退屏广告
		SsjjExitScreenManager.show(AppActivity.this, new OnExitScreenListener() {
			@Override
			public void onExit() {
				// 正式退出
				finish();
			}
			@Override
			public void onCancel() {
				// 取消退出
				SsjjExitScreenManager.preLoad(AppActivity.this); // 预加载退出插屏广告
			}
		}, "您确定退出么？", "退出", "取消");
	}
	
	@Override
	protected void onDestroy() {
		SsjjAdsManager.clearCache(AppActivity.this); // 清空缓存，for test
		super.onDestroy();
	}
	

	@Override
	public void onClick(View v) {
		
		switch (v.getId()) {
		
		//case R.id.btn_show_banner:
			// 测试使用不同布局参数时banner广告的展示效果
		//	addBanner(); 
		//	break;
			
		//case R.id.btn_show_pause_screen:
			// 设置超时不显示的超时时间 ,要在show之前调用[可选]
			//SsjjPauseScreenManager.setTimeout(5000);
			
			// 显示插屏广告
		//	SsjjPauseScreenManager.show(AppActivity.this, mOnSsjjAdsListener); 
			
			// 显示插屏广告，3秒后自动关闭,若小于3秒,则会自动设置为3秒
//			SsjjPauseScreenManager.show(MainActivity.this, mOnSsjjAdsListener, 3 * 1000); 
		//	break;
			
		//case R.id.btn_show_full_screen:
			// 设置超时不显示的超时时间 ,要在show之前调用[可选]
			//SsjjFullScreenManager.setTimeout(5000);
			
			// 显示全屏广告
			//SsjjFullScreenManager.show(MainActivity.this, mOnSsjjAdsListener);
			
			// 显示全屏广告，3秒后自动关闭,若小于3秒,则会自动设置为3秒
		//	SsjjFullScreenManager.show(AppActivity.this, mOnSsjjAdsListener, 3 * 1000);
		//	break;
			
		//case R.id.btn_clear_cache:
			// 清除广告缓存文件（积分墙除外）
		//	SsjjAdsManager.clearCache(AppActivity.this); 
		//	break;
		}
	}
	
	private SsjjAdsView mBanner; // banner广告
	
	private void showBanner() {
		mBanner = (SsjjAdsView) findViewById(R.id.banner);
		// 设置广告状态回调监听[可选]
		mBanner.setOnSsjjAdsListener(mOnSsjjAdsListener); 
		// 启用广告预加载[建议调用]
		mBanner.preLoad();   
		
		// 设置广告超时不显示的超时时间,要在show之前调用[可选]
		//mBanner.setTimeout(5000);
		
		// 设置广告切换时间为[默认为5秒]
		//mBanner.setFlipInterval(3000);
		
		// 设置横屏是否接收超长广告条[默认为接收]
		//mBanner.setEnableHorizonalAds(false);
		
		// 设置广告右上角的开关按钮是否显示[可选]
		//mBanner.enableCloseButton(false); 
		
		// 广告切换动画开关,默认为打开[可选]
		//mBanner.enableFlippingAnimation(false); 
		
		/* === 以下是设置广告尺寸相关，一般情况默认可满足需求  ===*/
		
		//mBanner.setSsjjAdsSize(SsjjAdsSize.SIZE_320x50_DP); // 设置为320 x 50，单位dp
		//mBanner.setSsjjAdsSize(SsjjAdsSize.SIZE_MATCH_PARENT); // 设置为width:匹配父view, height:包裹内容
		//mBanner.setSsjjAdsSize(480,60);    // 自定义广告尺寸，单位dp
		//mBanner.setSsjjAdsSizePx(480, 60); // 自定义广告尺寸，单位px
		
		// 重要方法，必须手动调用 show方法, banner广告才会显示
		mBanner.show(); 
	}
	
	private LinearLayout bannerLayout; //本demo中放置banner广告的容器
		
	// 使用代码方式动态生成 banner广告
	private void addBanner() {
		
		final SsjjAdsView banner = new SsjjAdsView(AppActivity.this);
		LayoutParams params = new LayoutParams(LayoutParams.MATCH_PARENT, LayoutParams.WRAP_CONTENT);
		//bannerLayout为容纳banner的父view
		bannerLayout.addView(banner, params); 
		
		// 监听获取到的广告图片的大小[自定义布局可参考使用]
		banner.setOnGetAdsSizeListener(new OnGetAdsSizeListener() {
			@Override
			public void onGetAdsSize(SsjjAdsView view, int widthPx, int heightPx) {
				// 得到广告图片的大小，这里可以进行重新设置布局 
				float ratio = widthPx / heightPx; //计算获取的广告的宽高比
				int widthDp = 300; // 自定义广告的宽度
				banner.setSsjjAdsSize(widthDp, (int) (widthDp / ratio));
			}
		});
		// 必须手动调用 show方法, banner广告才会显示
//		banner.setTimeout(200);
		banner.show(); 
	}
	
	/**
	 *  广告的回调接口
	 */
	private OnSsjjAdsListener mOnSsjjAdsListener = new OnSsjjAdsListener() {
		@Override
		public void onShow() {
			//广告正常显示时回调
			Log.i(TAG, "展示成功");
		}

		@Override
		public void onShowFailed() {
			// 显示广告失败或者加载超时会回调。
			Log.i(TAG, "展示失败");
		}

		@Override
		public void onDismiss() {
			// 广告消失时回调
			Log.i(TAG, "关闭展示");
		}

	};
	
	/* ===================== 方便测试而使用的代码 ======================== */
	
	private void updataTitle(){
		String idKey = "";
		String appKey = "";
		try {
			ApplicationInfo appinfo = getPackageManager().getApplicationInfo(getPackageName(),
					PackageManager.GET_META_DATA);
			if(appinfo.metaData != null) {
				idKey = "" + appinfo.metaData.getInt("IdKey");
				appKey = "" + appinfo.metaData.getInt("AppKey");
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		String str = "[appKey: " + appKey + "]";
		setTitle("4399广告SDK " + SsjjAdsManager.VERSION + str); // 方便测试
	}
	
	// dp 转 px
	public int dip2px(float dpValue) {
		final float scale = getResources().getDisplayMetrics().density;
		return (int) (dpValue * scale + 0.5f);
	}
	
	// px 转 dp
	public int px2dip(int pxValue) { 
		final float scale = getResources().getDisplayMetrics().density;
		return (int) (pxValue / scale + 0.5f);
	}

	
}
