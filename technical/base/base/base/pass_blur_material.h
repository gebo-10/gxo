#ifndef PASS_BLUR_MATERIAL_H
#define PASS_BLUR_MATERIAL_H
#include "material.h"
class BlurMaterial : public TextureMaterial {
public:
	int blurRadius;
	float blurStep;
	float kernelLength = 31 * 30;

	int mWidth;
	int mHeight;
	float mDirectionx;
	float mDirectiony;
	BlurMaterial(int width, int height) :TextureMaterial(nullptr) {
		string vs = "main/shader/blur.vert.glsl";
		string	fs = "main/shader/blur.frag.glsl";
		auto shader = std::make_shared<Shader>(vs, fs);
		set_shader(shader);

		mWidth = width;
		mHeight = height;
		init();
	}

	virtual void bind() {
		TextureMaterial::bind();

		int location = glGetUniformLocation(shader->gpu_id, "blurRadius");
		glUniform1i(location, blurRadius);

		location = glGetUniformLocation(shader->gpu_id, "blurStep");
		glUniform1f(location, blurStep);

		location = glGetUniformLocation(shader->gpu_id, "maskOffset");
		glUniform2f(location, mDirectionx, mDirectiony);


	}
	void init() {
		blurRadius = 30;
		blurStep = 1.0f / mWidth;
		shader->bind();
		int nameHandle = glGetUniformLocation(shader->gpu_id, "kernel");
		glUniform1fv(nameHandle, kernelLength, GAUSS_KERNEL);

	}
	void set_texture(TexturePtr texture) {
		this->texture = texture;
	}

	void set_direction(float x, float y) {
		mDirectionx = x / mWidth;
		mDirectiony = y / mHeight;
	}
	void set_radius(int radius) {
		if (radius > 30) {
			error("setRadius: radius must <  30");
			return;
		}
		blurRadius = radius;
	}
	int get_radius() {
		return blurRadius;
	}


	float GAUSS_KERNEL[31 * 30] = {
		(float)0.5, (float)0.25, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.375, (float)0.25, (float)0.0625, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.28125, (float)0.21875, (float)0.109375, (float)0.03125, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.236384, (float)0.198829, (float)0.118323, (float)0.0498173, (float)0.0148395, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.200565, (float)0.176998, (float)0.121649, (float)0.0651141, (float)0.0271436, (float)0.00881223, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.174219, (float)0.158506, (float)0.119371, (float)0.0744144, (float)0.0383987, (float)0.0164013, (float)0.00579888, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.15401, (float)0.143029, (float)0.114567, (float)0.0791492, (float)0.0471617, (float)0.0242375, (float)0.0107434, (float)0.00410725, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.103153, (float)0.0999789, (float)0.0910319, (float)0.0778637, (float)0.0625652, (float)0.0472267, (float)0.0334888, (float)0.0223083, (float)0.0139602, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.101487, (float)0.0983644, (float)0.0895618, (float)0.0766063, (float)0.0615549, (float)0.0464641, (float)0.032948, (float)0.0219481, (float)0.0137348, (float)0.00807425, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.10059, (float)0.097495, (float)0.0887702, (float)0.0759292, (float)0.0610108, (float)0.0460534, (float)0.0326567, (float)0.0217541, (float)0.0136133, (float)0.00800288, (float)0.00441961, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.100131, (float)0.0970499, (float)0.088365, (float)0.0755826, (float)0.0607323, (float)0.0458431, (float)0.0325077, (float)0.0216548, (float)0.0135512, (float)0.00796634, (float)0.00439943, (float)0.0022824, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.0999084, (float)0.0968345, (float)0.0881688, (float)0.0754148, (float)0.0605975, (float)0.0457414, (float)0.0324355, (float)0.0216067, (float)0.0135211, (float)0.00794866, (float)0.00438967, (float)0.00227733, (float)0.00110988, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.0998069, (float)0.0967362, (float)0.0880793, (float)0.0753382, (float)0.060536, (float)0.0456949, (float)0.0324026, (float)0.0215848, (float)0.0135074, (float)0.00794059, (float)0.00438521, (float)0.00227502, (float)0.00110875, (float)0.000507625, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.0997634, (float)0.096694, (float)0.0880409, (float)0.0753053, (float)0.0605095, (float)0.045675, (float)0.0323884, (float)0.0215753, (float)0.0135015, (float)0.00793712, (float)0.0043833, (float)0.00227402, (float)0.00110827, (float)0.000507403, (float)0.000218231, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.0997458, (float)0.0966769, (float)0.0880253, (float)0.0752921, (float)0.0604989, (float)0.0456669, (float)0.0323827, (float)0.0215715, (float)0.0134991, (float)0.00793573, (float)0.00438252, (float)0.00227362, (float)0.00110808, (float)0.000507314, (float)0.000218193, (float)8.81579e-005, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.0518933, (float)0.0514895, (float)0.0502967, (float)0.0483699, (float)0.0457957, (float)0.0426863, (float)0.0391711, (float)0.0353882, (float)0.0314749, (float)0.0275603, (float)0.0237585, (float)0.0201636, (float)0.0168473, (float)0.0138582, (float)0.0112227, (float)0.00894753, (float)0.007023, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.0513361, (float)0.0509366, (float)0.0497567, (float)0.0478505, (float)0.045304, (float)0.0422279, (float)0.0387505, (float)0.0350082, (float)0.0311369, (float)0.0272644, (float)0.0235034, (float)0.0199471, (float)0.0166664, (float)0.0137094, (float)0.0111022, (float)0.00885146, (float)0.00694759, (float)0.00536868, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.0509202, (float)0.0505239, (float)0.0493535, (float)0.0474628, (float)0.0449369, (float)0.0418858, (float)0.0384366, (float)0.0347245, (float)0.0308846, (float)0.0270435, (float)0.023313, (float)0.0197854, (float)0.0165314, (float)0.0135983, (float)0.0110123, (float)0.00877974, (float)0.0068913, (float)0.00532518, (float)0.00405118, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.050613, (float)0.0502192, (float)0.0490558, (float)0.0471765, (float)0.0446658, (float)0.0416331, (float)0.0382047, (float)0.0345151, (float)0.0306984, (float)0.0268804, (float)0.0231723, (float)0.0196661, (float)0.0164316, (float)0.0135163, (float)0.0109458, (float)0.00872678, (float)0.00684973, (float)0.00529306, (float)0.00402675, (float)0.00301589, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.0503889, (float)0.0499968, (float)0.0488386, (float)0.0469676, (float)0.0444681, (float)0.0414488, (float)0.0380356, (float)0.0343623, (float)0.0305624, (float)0.0267614, (float)0.0230697, (float)0.019579, (float)0.0163589, (float)0.0134565, (float)0.0108974, (float)0.00868814, (float)0.0068194, (float)0.00526962, (float)0.00400892, (float)0.00300254, (float)0.00221393, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.0502275, (float)0.0498366, (float)0.0486821, (float)0.0468172, (float)0.0443256, (float)0.041316, (float)0.0379137, (float)0.0342522, (float)0.0304645, (float)0.0266756, (float)0.0229958, (float)0.0195163, (float)0.0163065, (float)0.0134133, (float)0.0108625, (float)0.0086603, (float)0.00679755, (float)0.00525274, (float)0.00399607, (float)0.00299292, (float)0.00220684, (float)0.00160199, 0, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.0501127, (float)0.0497227, (float)0.0485709, (float)0.0467102, (float)0.0442243, (float)0.0412216, (float)0.0378271, (float)0.0341739, (float)0.0303949, (float)0.0266147, (float)0.0229433, (float)0.0194717, (float)0.0162692, (float)0.0133827, (float)0.0108376, (float)0.00864052, (float)0.00678202, (float)0.00524074, (float)0.00398694, (float)0.00298608, (float)0.0022018, (float)0.00159834, (float)0.00114228, 0, 0, 0, 0, 0, 0, 0, 0,
			(float)0.0500323, (float)0.049643, (float)0.048493, (float)0.0466352, (float)0.0441534, (float)0.0411555, (float)0.0377664, (float)0.0341191, (float)0.0303461, (float)0.026572, (float)0.0229065, (float)0.0194405, (float)0.0162431, (float)0.0133612, (float)0.0108202, (float)0.00862665, (float)0.00677114, (float)0.00523233, (float)0.00398055, (float)0.00298129, (float)0.00219827, (float)0.00159577, (float)0.00114045, (float)0.000802404, 0, 0, 0, 0, 0, 0, 0,
			(float)0.0346711, (float)0.0345509, (float)0.0341929, (float)0.0336044, (float)0.0327974, (float)0.0317884, (float)0.0305971, (float)0.0292467, (float)0.0277624, (float)0.0261711, (float)0.0245003, (float)0.0227774, (float)0.0210291, (float)0.0192806, (float)0.0175552, (float)0.0158736, (float)0.0142537, (float)0.0127106, (float)0.011256, (float)0.009899, (float)0.00864531, (float)0.00749815, (float)0.0064582, (float)0.00552399, (float)0.00469222, 0, 0, 0, 0, 0, 0,
			(float)0.0343988, (float)0.0342795, (float)0.0339243, (float)0.0333404, (float)0.0325398, (float)0.0315387, (float)0.0303568, (float)0.029017, (float)0.0275444, (float)0.0259655, (float)0.0243078, (float)0.0225985, (float)0.0208639, (float)0.0191292, (float)0.0174173, (float)0.0157489, (float)0.0141418, (float)0.0126107, (float)0.0111676, (float)0.00982125, (float)0.00857741, (float)0.00743925, (float)0.00640747, (float)0.0054806, (float)0.00465537, (float)0.00392702, 0, 0, 0, 0, 0,
			(float)0.0341739, (float)0.0340555, (float)0.0337026, (float)0.0331225, (float)0.0323271, (float)0.0313325, (float)0.0301584, (float)0.0288273, (float)0.0273643, (float)0.0257958, (float)0.0241489, (float)0.0224507, (float)0.0207275, (float)0.0190041, (float)0.0173035, (float)0.015646, (float)0.0140493, (float)0.0125283, (float)0.0110946, (float)0.00975705, (float)0.00852134, (float)0.00739063, (float)0.00636559, (float)0.00544478, (float)0.00462494, (float)0.00390135, (float)0.0032682, 0, 0, 0, 0,
			(float)0.0339891, (float)0.0338713, (float)0.0335203, (float)0.0329434, (float)0.0321523, (float)0.0311631, (float)0.0299953, (float)0.0286714, (float)0.0272163, (float)0.0256563, (float)0.0240183, (float)0.0223293, (float)0.0206154, (float)0.0189014, (float)0.0172099, (float)0.0155613, (float)0.0139733, (float)0.0124605, (float)0.0110346, (float)0.00970428, (float)0.00847526, (float)0.00735066, (float)0.00633116, (float)0.00541533, (float)0.00459992, (float)0.00388026, (float)0.00325053, (float)0.00270416, 0, 0, 0,
			(float)0.0338379, (float)0.0337206, (float)0.0333712, (float)0.0327968, (float)0.0320093, (float)0.0310245, (float)0.0298618, (float)0.0285439, (float)0.0270953, (float)0.0255422, (float)0.0239115, (float)0.02223, (float)0.0205237, (float)0.0188173, (float)0.0171333, (float)0.0154921, (float)0.0139112, (float)0.0124051, (float)0.0109856, (float)0.00966112, (float)0.00843756, (float)0.00731796, (float)0.006303, (float)0.00539124, (float)0.00457946, (float)0.00386299, (float)0.00323607, (float)0.00269213, (float)0.00222412, 0, 0,
			(float)0.0337149, (float)0.033598, (float)0.0332498, (float)0.0326776, (float)0.0318929, (float)0.0309117, (float)0.0297533, (float)0.0284401, (float)0.0269968, (float)0.0254493, (float)0.0238246, (float)0.0221492, (float)0.0204491, (float)0.0187489, (float)0.017071, (float)0.0154358, (float)0.0138606, (float)0.01236, (float)0.0109456, (float)0.00962599, (float)0.00840688, (float)0.00729135, (float)0.00628008, (float)0.00537164, (float)0.00456281, (float)0.00384895, (float)0.0032243, (float)0.00268234, (float)0.00221603, (float)0.00181811, 0,
			(float)0.0336153, (float)0.0334988, (float)0.0331516, (float)0.032581, (float)0.0317987, (float)0.0308203, (float)0.0296654, (float)0.0283561, (float)0.026917, (float)0.0253741, (float)0.0237542, (float)0.0220837, (float)0.0203887, (float)0.0186935, (float)0.0170206, (float)0.0153902, (float)0.0138197, (float)0.0123235, (float)0.0109133, (float)0.00959755, (float)0.00838204, (float)0.00726981, (float)0.00626153, (float)0.00535577, (float)0.00454933, (float)0.00383758, (float)0.00321478, (float)0.00267441, (float)0.00220948, (float)0.00181274, (float)0.00147695
	};



};
typedef shared_ptr<BlurMaterial> BlurMaterialPtr;

#endif
