uniform sampler2DRect src_tex_unit0;
uniform float blurAmnt;
uniform float divAmt;

void main( void )
{  
	vec2 st = gl_TexCoord[0].st;

	//horizontal blur
	//from http://www.gamerendering.com/2008/10/11/gaussian-blur-filter-shader/
	
	vec4 color;
	
	color		+= 1.0 * texture2DRect(src_tex_unit0, st + vec2(blurAmnt * -4.0, 0.0));
	color		+= 2.0 * texture2DRect(src_tex_unit0, st + vec2(blurAmnt * -3.0, 0.0));
	color		+= 3.0 * texture2DRect(src_tex_unit0, st + vec2(blurAmnt * -2.0, 0.0));
	color		+= 4.0 * texture2DRect(src_tex_unit0, st + vec2(blurAmnt * -1.0, 0.0));	
		
	color		+= 5.0 * texture2DRect(src_tex_unit0, st + vec2(blurAmnt, 0));
	
	color		+= 4.0 * texture2DRect(src_tex_unit0, st + vec2(blurAmnt * 1.0, 0.0));
	color		+= 3.0 * texture2DRect(src_tex_unit0, st + vec2(blurAmnt * 2.0, 0.0));
	color		+= 2.0 * texture2DRect(src_tex_unit0, st + vec2(blurAmnt * 3.0, 0.0));
	color		+= 1.0 * texture2DRect(src_tex_unit0, st + vec2(blurAmnt * 4.0, 0.0));
    
    color /= 25.0;
//    float blurAmnt2 = blurAmnt*2500.0;
//	color[0] /= (blurAmnt2);
//    color[1] /= (blurAmnt2);
//    color[2] /= (blurAmnt2);
//    color[3] /= (blurAmnt2);
    
	gl_FragColor = color;
}