#include "Includes.h"
#include "obfuscate.h"
#include "Tools.h"
#include "fake_dlfcn.h"
#include "imgui/imgui.h"
#include "imgui/backends/imgui_impl_android.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "StrEnc.h"
#include "Spoof.h"
#include "plthook.h"
#include "Items.h"
#include "Iconcpp.h"
#include "Icon.h"
#include "json.hpp"
#include "KittyMemory/MemoryPatch.h"
#include "Color.h"
#include "CN.h"
#include "Font.h"
#include "Vector3.hpp"
#include "foxcheats/include/ScanEngine.hpp"
using json = nlohmann::json;
#include "Includes/Logger.h"
#include "Includes/Utils.h"
#include "Includes/Toast.hpp"
#include "Includes/Macros.h"
#include <list>
#include <vector>
#include <cstring>
#include <pthread.h>
#include <thread>
#include <cstring>
#include <jni.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <dlfcn.h>
 
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <sys/limits.h>
#include <sys/mman.h>
#include "SDK.hpp"

using namespace SDK;

#include <curl/curl.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include "base64/base64.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

#define GEngine_Offset 0xb51bb48
#define GNames_Offset 0x6715794
#define GUObject_Offset 0xb31ec40
#define GetActorArray 0x7fda270
#define CanvasMap_Offsets 0xb4f5dc8
#define GNativeAndroidApp_Offset 0xb0bfb68

#define Actors_Offset 0xA0

#define targetLibName OBFUSCATE("libUE4.so")
#define targetLibName OBFUSCATE("libanogs.so")
#define targetLibName OBFUSCATE("libanort.so")
#define targetLibName OBFUSCATE("libhdmpve.so")

std::map<std::string, u_long> Config;
char extra[32];
std::map<int, bool> Items;
std::map<int, float *> ItemColors;
std::map<int, bool> itemConfig;
json itemData;
json items_data;
std::string g_Token, g_Auth;
bool bValid = false;
using namespace std;
bool EnimiesAlertNhk = true;
using namespace kFox;

static char chars[64];
static char dword[64];

//===@JAGDISH_VIP======KEY====EXP=================
std::string Bullet,Memory,AimBot,Extra;
time_t rng = 0;
static std::string BHATIA_EXP = "";
static std::string BHATIA_SLOT = "";
static std::string ModName64 = "";
static std::string MOD_STATUS64 = "";
static std::string FLOTING_TEST64 = "";


//=====@JAGDISH_VIP========掳



uintptr_t UE4;
uintptr_t anort;
uintptr_t anogs;
uintptr_t AntsVoice;
uintptr_t hdmpve;
android_app *g_App = 0;
ASTExtraPlayerCharacter *g_LocalPlayer = 0;
ASTExtraPlayerController *g_LocalController = 0;

bool HIDEESP = true;
bool initImGui = false;
int screenWidth = -1, glWidth, screenHeight = -1, glHeight;
float density = -1;

static UEngine *GEngine = 0;

UWorld *GetWorld() {
    while (!GEngine) {
 GEngine = UObject::FindObject<UEngine>("UAEGameEngine Transient.UAEGameEngine_1");
        sleep(1);
          }
    if (GEngine) {
    auto ViewPort = GEngine->GameViewport;
     if (ViewPort) {
   return ViewPort->World;
     }   }
    return 0;
       }



TNameEntryArray *GetGNames() {
    return ((TNameEntryArray *(*)()) (UE4 + GNames_Offset))();
}

std::vector<AActor *> getActors() {
    auto World = GetWorld();
    if (!World)
        return std::vector<AActor *>();

    auto PersistentLevel = World->PersistentLevel;
    if (!PersistentLevel)
        return std::vector<AActor *>();

    auto Actors = *(TArray<AActor *> *)((uintptr_t) PersistentLevel + Actors_Offset);

    std::vector<AActor *> actors;
    for (int i = 0; i < Actors.Num(); i++) {
        auto Actor = Actors[i];
        if (Actor) {
            actors.push_back(Actor);
        }
    }
    return actors;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

enum EAimTarget {
    Head = 0,
    Chest = 1
};

enum EAimTrigger {
    None = 0,
    Shooting = 1,
    Scoping = 2,
    Both = 3,
    Any = 4
};

struct sDemon {
    struct sPlayerESP {
        bool Line;
        bool Box;
        bool Health;
        bool Skeleton;
        bool Name;
        bool Distance;
        bool TeamID;
        bool Vehicle;
        bool NoBot;
    };

    sPlayerESP PlayerESP{0};

    struct sAimMenu {
        bool Enable;
        bool AimBot;
        EAimTarget Target;
        EAimTrigger Trigger;
        bool IgnoreKnocked;
        bool IgnoreBot;
        bool VisCheck;
    };
    sAimMenu SilentAim{0};
    sAimMenu AimBot{0};

    struct sHighRisk {
        bool Shake;
        bool Recoil;
        bool Instant;
        bool HitEffect;
        bool Flash;
        bool Parachute;
    };
    sHighRisk HighRisk{0};

    struct sOTHER {
        bool FPS;
        bool HIDEESP;
    };
    sOTHER OTHER{0};

  struct sColorsESP {
        float *Line;
        float *Box;
        float *Name;
        float *Distance;
        float *Skeleton;
        float *SkeletonVisible;

        float *Vehicle;
    };
    sColorsESP ColorsESP{0};
    
};
sDemon Demon{0};


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

#define CREATE_COLOR(r, g, b, a) new float[4] {(float)r, (float)g, (float)b, (float)a};

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\


struct sRegion {
    uintptr_t start, end;
};

std::vector<sRegion> trapRegions;

bool isObjectInvalid(UObject *obj) {
    if (!Tools::IsPtrValid(obj)) {
        return true;
    }

    if (!Tools::IsPtrValid(obj->ClassPrivate)) {
        return true;
    }

    if (obj->InternalIndex <= 0) {
        return true;
    }

    if (obj->NamePrivate.ComparisonIndex <= 0) {
        return true;
    }

    if ((uintptr_t)(obj) % sizeof(uintptr_t) != 0x0 && (uintptr_t)(obj) % sizeof(uintptr_t) != 0x4) {
        return true;
    }

    if (std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj) >= region.start && ((uintptr_t) obj) <= region.end; }) ||
        std::any_of(trapRegions.begin(), trapRegions.end(), [obj](sRegion region) { return ((uintptr_t) obj->ClassPrivate) >= region.start && ((uintptr_t) obj->ClassPrivate) <= region.end; })) {
        return true;
    }

    return false;
}



typedef void (*ImGuiDemoMarkerCallback)(const char* file, int line, const char* section, void* user_data);
extern ImGuiDemoMarkerCallback  GImGuiDemoMarkerCallback;
extern void* GImGuiDemoMarkerCallbackUserData;
ImGuiDemoMarkerCallback         GImGuiDemoMarkerCallback = NULL;
void* GImGuiDemoMarkerCallbackUserData = NULL;
#define IMGUI_DEMO_MARKER(section)  do { if (GImGuiDemoMarkerCallback != NULL) GImGuiDemoMarkerCallback(__FILE__, __LINE__, section, GImGuiDemoMarkerCallbackUserData); } while (0)
ImGuiStyle& style = ImGui::GetStyle();
static ImGuiStyle ref_saved_style;




//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

std::string getObjectPath(UObject *Object) {
    std::string s;
    for (auto super = Object->ClassPrivate; super; super = (UClass *) super->SuperStruct) {
        if (!s.empty())
            s += ".";
        s += super->NamePrivate.GetName();
    }
    return s;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

int32_t ToColor(float *col) {
    return ImGui::ColorConvertFloat4ToU32(*(ImVec4 *) (col));
}

FRotator ToRotator(FVector local, FVector target) {
    FVector rotation = UKismetMathLibrary::Subtract_VectorVector(local, target);

    float hyp = sqrt(rotation.X * rotation.X + rotation.Y * rotation.Y);

    FRotator newViewAngle = {0};
    newViewAngle.Pitch = -atan(rotation.Z / hyp) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Yaw = atan(rotation.Y / rotation.X) * (180.f / (float) 3.14159265358979323846);
    newViewAngle.Roll = (float) 0.f;

    if (rotation.X >= 0.f)
        newViewAngle.Yaw += 180.0f;

    return newViewAngle;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

#define W2S(w, s) UGameplayStatics::ProjectWorldToScreen(localController, w, true, s)

bool isAimInsideFOV(int x,int y)
{
    if(!Config["HACK::ENABLE"])
        return true;
        
        int circle_x = glWidth / 2;
        int circle_y = glHeight / 2;
        int rad = Config["FOV::SIZE"];
        return (x - circle_x) * (x - circle_x) + (y - circle_y) * (y - circle_y) <= rad * rad;
}

auto GetTargetForAimBot() {
	ASTExtraPlayerCharacter * result = 0;
	float max = std::numeric_limits<float>::infinity();
	auto Actors = getActors();
	auto localPlayer = g_LocalPlayer;
	auto localController = g_LocalController;
	if (localPlayer) {
		for (auto Actor : Actors) {
			if (isObjectInvalid(Actor))
				continue;
			if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
				auto Player = (ASTExtraPlayerCharacter *)Actor;
				if (Player->PlayerKey == localPlayer->PlayerKey)
					continue;
				if (Player->TeamID == localPlayer->TeamID)
					continue;
				if (Player->bDead)
					continue;
				if (Config["HACK::IGKNOCK"]) {
					if (Player->Health == 0.0f)
						continue;
				}
				if (Config["HACK::VISICHECK"]) {
					if (!localController->LineOfSightTo(Player, {0, 0, 0}, true))
						continue;
				}
				if (Config["HACK::IGBOT"]) {
					if (Player->bIsAI)
						continue;
				}
				auto Root = Player->GetBonePos("Root", {});
				auto Head = Player->GetBonePos("Head", {});
				FVector2D RootSc, HeadSc;
				if (W2S(Root, & RootSc) && W2S(Head, & HeadSc)) {
					float height = abs(HeadSc.Y - RootSc.Y);
					float width = height * 0.65f;
					FVector middlePoint = {HeadSc.X + (width / 2), HeadSc.Y + (height / 2), 0};
					if ((middlePoint.X >= 0 && middlePoint.X <= glWidth) && (middlePoint.Y >= 0 && middlePoint.Y <= glHeight)) {
						FVector2D v2Middle = FVector2D((float)(glWidth / 2), (float)(glHeight / 2));
						FVector2D v2Loc = FVector2D(middlePoint.X, middlePoint.Y);
						    if (isAimInsideFOV((int)middlePoint.X, (int)middlePoint.Y)) {
						float dist = FVector2D::Distance(v2Middle, v2Loc);
						if (dist < max) {
							max = dist;
							result = Player;
						}
					}}
				}
			}
		}
	}
	return result;
}
//=======饾棧饾棓饾棞饾棗==饾棪饾棩饾棖==饾棟饾棦饾棞饾棥==饾棫饾棙饾棢饾棙饾棜饾棩饾棓饾棤=@饾棜饾棡饾棧饾棛饾棩饾棙饾棙饾棝饾棓饾棖饾棡饾棪======= //




auto GetCurrentWeaponReplicated(ASTExtraPlayerCharacter * Akshat) {
	auto WeaponManagerComponent = Akshat->WeaponManagerComponent;
	if (WeaponManagerComponent) {
		auto propSlot = WeaponManagerComponent->GetCurrentUsingPropSlot();
		if ((int)propSlot.GetValue() >= 1 && (int)propSlot.GetValue() <= 3) {
			return (ASTExtraShootWeapon *)WeaponManagerComponent->CurrentWeaponReplicated;
		}
	}
}

const char *GetVehicleName(ASTExtraVehicleBase *Vehicle) {
    switch (Vehicle->VehicleShapeType) {
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Motorbike_SideCart:
            return "Motorbike";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Dacia:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyDacia:
            return "Dacia";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MiniBus:
            return "Mini Bus";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PickUp01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyPickup:
            return "Pick Up";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Buggy:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyBuggy:
            return "Buggy";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ01:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ02:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAZ03:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUAZ:
            return "UAZ";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_PG117:
            return "PG117";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Aquarail:
            return "Aquarail";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Mirado01:
            return "Mirado";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Rony:
            return "Rony";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Scooter:
            return "Scooter";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowMobile:
            return "Snow Mobile";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_TukTukTuk:
            return "Tuk Tuk";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_SnowBike:
            return "Snow Bike";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Surfboard:
            return "Surf Board";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Snowboard:
            return "Snow Board";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Amphibious:
            return "Amphibious";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_LadaNiva:
            return "Lada Niva";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_UAV:
            return "UAV";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_MegaDrop:
            return "Mega Drop";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini:
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_Lamborghini01:
            return "Lamborghini";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_GoldMirado:
            return "Gold Mirado";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_BigFoot:
            return "Big Foot";
            break;
        case ESTExtraVehicleShapeType::ESTExtraVehicleShapeType__VST_HeavyUH60:
            return "UH60";
            break;
        default:
            return "Vehicle";
            break;
    }
    return "Vehicle";
}


// FOV AIM BOT





//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

class FPSCounter {
protected:
    unsigned int m_fps;
    unsigned int m_fpscount;
    long m_fpsinterval;

public:
    FPSCounter() : m_fps(0), m_fpscount(0), m_fpsinterval(0) {
    }

    void update() {
        m_fpscount++;

        if (m_fpsinterval < time(0)) {
            m_fps = m_fpscount;

            m_fpscount = 0;
            m_fpsinterval = time(0) + 1;
        }
    }

    unsigned int get() const {
        return m_fps;
    }
};

FPSCounter fps;
class Rect {
public:
    float x;
    float y;
    float width;
    float height;

    Rect() {
        this->x = 0;
        this->y = 0;
        this->width = 0;
        this->height = 0;
    }

    Rect(float x, float y, float width, float height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }

    bool operator==(const Rect &src) const {
        return (src.x == this->x && src.y == this->y && src.height == this->height &&
                src.width == this->width);
    }

    bool operator!=(const Rect &src) const {
        return (src.x != this->x && src.y != this->y && src.height != this->height &&
                src.width != this->width);
    }
};

static float isRed = 0.0f, isGreen = 0.01f, isBlue = 0.0f;
void DrawESP(ImDrawList *draw) {
	

	
	if (g_Token.empty())
        return;

    if (g_Auth.empty())
        return;

    if (g_Token != g_Auth)
        return;
	
	auto isFrames = ImGui::GetFrameCount();
	    if(isFrames % 1 == 0) {

        if(isGreen == 0.01f && isBlue == 0.0f){
            isRed += 0.01f;
             }

        if(isRed > 0.99f && isBlue == 0.0f){
            isRed = 1.0f;
            isGreen += 0.01f;
            }

        if(isGreen > 0.99f && isBlue == 0.0f){
            isGreen = 1.0f;
            isRed -= 0.01f;
        }

       if(isRed < 0.01f && isGreen == 1.0f){
            isRed = 0.0f;
            isBlue += 0.01f;
            }

        if(isBlue > 0.99f && isRed == 0.0f){
            isBlue = 1.0f;
            isGreen -= 0.01f;
            }
        if(isGreen < 0.01f && isBlue == 1.0f){
            isGreen = 0.0f;
            isRed += 0.01f;
            }
        if(isRed > 0.99f && isGreen == 0.0f){
            isRed = 1.0f;
            isBlue -= 0.01f;
            }
        if(isBlue < 0.01f && isGreen == 0.0f){
            isBlue = 0.0f;
            isRed -= 0.01f;
            if(isRed < 0.01f)
            isGreen = 0.01f;
        }
 
    }
	


	
	std::string sExpiredDate = ("");
    sExpiredDate += BHATIA_EXP.c_str();
   draw->AddText(NULL, ((float) density / 18.0f),{(float) glWidth / 50 + glWidth / 40,650},IM_COL32(255, 000, 000, 255),sExpiredDate.c_str());
   
   
   draw->AddText(NULL, ((float) density / 10.0f),{(float) glWidth / 150 + glWidth / 35,610},IM_COL32(255, 000, 000, 255),
                          "");
	
				std::string sFLOTINGTEST64 = ("");
    sFLOTINGTEST64 += FLOTING_TEST64.c_str();
   draw->AddText(NULL, ((float) density / 18.0f),{(float) glWidth / 50 + glWidth / 40,670},IM_COL32(255, 000, 000, 255), sFLOTINGTEST64.c_str());		  
	
    if (Demon.OTHER.HIDEESP) {
        HIDEESP = false;
    } else {
        HIDEESP = true;
    }
    if (HIDEESP) {

        auto Actors = getActors();

        int totalEnemies = 0, totalBots = 0;

        ASTExtraPlayerCharacter *localPlayer = 0;
        ASTExtraPlayerController *localController = 0;


        std::string sFPS = "FPS: ";
        sFPS += std::to_string(fps.get());

        if (Demon.OTHER.FPS) {
            draw->AddText({((float) density / 10.0f), 40}, IM_COL32(255, 000, 000, 255),
                          sFPS.c_str());
        }


        for (int i = 0; i < Actors.size(); i++) {
			auto Actor = Actors[i];
			if (isObjectInvalid(Actor))
				continue;
			if (Actor->IsA(ASTExtraPlayerController::StaticClass())) {
				localController = (ASTExtraPlayerController *)Actor;
				break;
			}
		}
		if (localController) {
			for (int i = 0; i < Actors.size(); i++) {
				auto Actor = Actors[i];
				if (isObjectInvalid(Actor))
					continue;
				if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
					if (((ASTExtraPlayerCharacter *)Actor)->PlayerKey == localController->PlayerKey) {
						localPlayer = (ASTExtraPlayerCharacter *)Actor;
						break;
					}
				}
			}
			if (localPlayer) {
				if (localPlayer->PartHitComponent) {
					auto ConfigCollisionDistSqAngles = localPlayer->PartHitComponent->ConfigCollisionDistSqAngles;
					for (int j = 0; j < ConfigCollisionDistSqAngles.Num(); j++) {
						ConfigCollisionDistSqAngles[j].Angle = 90.0f;
					}
					localPlayer->PartHitComponent->ConfigCollisionDistSqAngles = ConfigCollisionDistSqAngles;
				}
				
				
				
				
				if (Config["HACK::ENABLE"]) {
					if(Config["HACK::TYPE"] ==0){
					ASTExtraPlayerCharacter * Target = GetTargetForAimBot();
					if (Target) {
						bool triggerOk = false;
						if (Config["AIM::TRIGGER"] != 0) {
							if (Config["AIM::TRIGGER"] == 1) {
								triggerOk = localPlayer->bIsWeaponFiring;
							} else if (Config["AIM::TRIGGER"] == 2) {
								triggerOk = localPlayer->bIsGunADS;
							} else if (Config["AIM::TRIGGER"] == 3) {
								triggerOk = localPlayer->bIsWeaponFiring && localPlayer->bIsGunADS;
							} else if (Config["AIM::TRIGGER"] == 4) {
								triggerOk = localPlayer->bIsWeaponFiring || localPlayer->bIsGunADS;
							}
						} else
							triggerOk = true;
						if (triggerOk) {
							FVector targetAimPos = Target->GetBonePos("Head", {});
							if (Config["AIM::AIMPOS"] == 1) {
								targetAimPos.Z -= 25.0f;
							}
							auto CurrentWeaponReplicated = GetCurrentWeaponReplicated(localPlayer);
							if (CurrentWeaponReplicated) {
								auto ShootWeaponComponent = CurrentWeaponReplicated->ShootWeaponComponent;
								if (ShootWeaponComponent) {
									UShootWeaponEntity * ShootWeaponEntityComponent = ShootWeaponComponent->ShootWeaponEntityComponent;
									if (ShootWeaponEntityComponent) {
										ASTExtraVehicleBase * CurrentVehicle = Target->CurrentVehicle;
										if (CurrentVehicle) {
											FVector LinearVelocity = CurrentVehicle->ReplicatedMovement.LinearVelocity;
											float dist = localPlayer->GetDistanceTo(Target);
											auto timeToTravel = dist / ShootWeaponEntityComponent->BulletFireSpeed;
											targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(LinearVelocity, timeToTravel));
										} else {
											FVector Velocity = Target->GetVelocity();
											float dist = localPlayer->GetDistanceTo(Target);
											auto timeToTravel = dist / ShootWeaponEntityComponent->BulletFireSpeed;
											targetAimPos = UKismetMathLibrary::Add_VectorVector(targetAimPos, UKismetMathLibrary::Multiply_VectorFloat(Velocity, timeToTravel));
										}
								                                                
                                                if (Config["RECOIL::COMP"]) {
                                                    if (g_LocalPlayer->bIsGunADS) {
                                                        if (g_LocalPlayer->bIsWeaponFiring) {
                                                            float dist = g_LocalPlayer->GetDistanceTo(Target) / 100.f;                                                                                 
                                                            targetAimPos.Z -= dist * float(Config["RECOIL::SIZE"]);
                                                        }  
                                                    }
                                                }		
										localController->SetControlRotation(ToRotator(localController->PlayerCameraManager->CameraCache.POV.Location, targetAimPos), "");
									}
								}
							}
						}
					}
					}
				}
           


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\


                for (int i = 0; i < Actors.size(); i++) {
                    auto Actor = Actors[i];
                    if (isObjectInvalid(Actor))
                        continue;


                    if (Actor->IsA(ASTExtraPlayerCharacter::StaticClass())) {
                        auto Player = (ASTExtraPlayerCharacter *) Actor;

                        float Distance = localPlayer->GetDistanceTo(Player) / 100.0f;
                        if (Distance > 500.0f)
                            continue;

                        if (Player->PlayerKey == localController->PlayerKey)
                            continue;

                        if (Player->TeamID == localController->TeamID)
                            continue;

                        if (Player->bDead)
                            continue;

                        if (!Player->Mesh)
                            continue;

                        if (Player->bIsAI)
                            totalBots++;
                        else totalEnemies++;

                        if (Config["ESP::NOBOT"])
                            if (Player->bIsAI)
                                continue;

                            else totalEnemies++;

                        auto HeadPos = Player->GetBonePos("Head", {});
                        ImVec2 HeadPosSC;

                        auto RootPos = Player->GetBonePos("Root", {});
                        ImVec2 RootPosSC;

                        auto upper_r = Player->GetBonePos("upperarm_r", {});
                        ImVec2 upper_rPoSC;
                        auto lowerarm_r = Player->GetBonePos("lowerarm_r", {});
                        ImVec2 lowerarm_rPoSC;
                        auto hand_r = Player->GetBonePos("hand_r", {});
                        ImVec2 hand_rPoSC;
                        auto upper_l = Player->GetBonePos("upperarm_l", {});
                        ImVec2 upper_lPoSC;
                        auto lowerarm_l = Player->GetBonePos("lowerarm_l", {});
                        ImVec2 lowerarm_lSC;
                        auto hand_l = Player->GetBonePos("hand_l", {});
                        ImVec2 hand_lPoSC;
                        auto thigh_l = Player->GetBonePos("thigh_l", {});
                        ImVec2 thigh_lPoSC;
                        auto calf_l = Player->GetBonePos("calf_l", {});
                        ImVec2 calf_lPoSC;
                        auto foot_l = Player->GetBonePos("foot_l", {});
                        ImVec2 foot_lPoSC;
                        auto thigh_r = Player->GetBonePos("thigh_r", {});
                        ImVec2 thigh_rPoSC;
                        auto calf_r = Player->GetBonePos("calf_r", {});
                        ImVec2 calf_rPoSC;
                        auto foot_r = Player->GetBonePos("foot_r", {});
                        ImVec2 foot_rPoSC;
                        auto neck_01 = Player->GetBonePos("neck_01", {});
                        ImVec2 neck_01PoSC;
                        auto pelvis = Player->GetBonePos("pelvis", {});
                        ImVec2 pelvisPoSC;
                        bool IsVisible = localController->LineOfSightTo(Player, {0, 0, 0}, true);
                         int SCOLOR, SCOLOR2;

                    if (IsVisible)
                    {
                        SCOLOR = ToColor(Demon.ColorsESP.SkeletonVisible);
                        SCOLOR2 = IM_COL32(0, 255, 0, 255);
                    }else{
                        SCOLOR = ToColor(Demon.ColorsESP.Skeleton);
                        SCOLOR2 = IM_COL32(255, 255, 255, 255);
                    }

                        if (W2S(HeadPos, (FVector2D *) &HeadPosSC) &&
                            W2S(upper_r, (FVector2D *) &upper_rPoSC) &&
                            W2S(upper_l, (FVector2D *) &upper_lPoSC) &&
                            W2S(lowerarm_r, (FVector2D *) &lowerarm_rPoSC) &&
                            W2S(hand_r, (FVector2D *) &hand_rPoSC) &&
                            W2S(lowerarm_l, (FVector2D *) &lowerarm_lSC) &&
                            W2S(hand_l, (FVector2D *) &hand_lPoSC) &&
                            W2S(thigh_l, (FVector2D *) &thigh_lPoSC) &&
                            W2S(calf_l, (FVector2D *) &calf_lPoSC) &&
                            W2S(foot_l, (FVector2D *) &foot_lPoSC) &&
                            W2S(thigh_r, (FVector2D *) &thigh_rPoSC) &&
                            W2S(calf_r, (FVector2D *) &calf_rPoSC) &&
                            W2S(foot_r, (FVector2D *) &foot_rPoSC) &&
                            W2S(neck_01, (FVector2D *) &neck_01PoSC) &&
                            W2S(pelvis, (FVector2D *) &pelvisPoSC) &&
                            W2S(RootPos, (FVector2D *) &RootPosSC)) {

                            if (Config["ESP::LINE"]) {
                                draw->AddLine({(float) glWidth / 2, 0}, ImVec2(HeadPosSC.x, HeadPosSC.y - 55.0f), IM_COL32(255, 255, 000, 255), 1.5f);
                            }
							
							                              
							
							
							

                            if (Config["ESP::SKELETON"]) {
                                // ESP Head
                                draw->AddLine({upper_rPoSC.x, upper_rPoSC.y}, neck_01PoSC, SCOLOR, 1.5f);
                                draw->AddLine({upper_lPoSC.x, upper_lPoSC.y}, neck_01PoSC, SCOLOR, 1.5f);

                                draw->AddLine({upper_rPoSC.x, upper_rPoSC.y}, lowerarm_rPoSC, SCOLOR, 1.5f);
                                draw->AddLine({lowerarm_rPoSC.x, lowerarm_rPoSC.y}, hand_rPoSC, SCOLOR , 1.5f);

                                draw->AddLine({upper_lPoSC.x, upper_lPoSC.y}, lowerarm_lSC, SCOLOR, 1.5f);
                                draw->AddLine({lowerarm_lSC.x, lowerarm_lSC.y}, hand_lPoSC, SCOLOR, 1.5f);

                                draw->AddLine({thigh_rPoSC.x, thigh_rPoSC.y}, thigh_lPoSC, SCOLOR, 1.5f);

                                draw->AddLine({thigh_lPoSC.x, thigh_lPoSC.y}, calf_lPoSC, SCOLOR, 1.5f);
                                draw->AddLine({calf_lPoSC.x, calf_lPoSC.y}, foot_lPoSC, SCOLOR, 1.5f);

                                draw->AddLine({thigh_rPoSC.x, thigh_rPoSC.y}, calf_rPoSC, SCOLOR, 1.5f);
                                draw->AddLine({calf_rPoSC.x, calf_rPoSC.y}, foot_rPoSC, SCOLOR, 1.5f);

                                draw->AddLine({neck_01PoSC.x, neck_01PoSC.y}, pelvisPoSC, SCOLOR, 1.5f);
                                draw->AddLine({neck_01PoSC.x, neck_01PoSC.y}, HeadPosSC, SCOLOR, 1.5f);

                            }
                            if (Config["ESP::BOX"]) {
                                float boxHeight = abs(HeadPosSC.y - RootPosSC.y);
                                    float boxWidth = boxHeight * 0.65f;
                                    ImVec2 vStart = {HeadPosSC.x - (boxWidth / 2), HeadPosSC.y};
                                    ImVec2 vEnd = {vStart.x + boxWidth, vStart.y + boxHeight};

                                    draw->AddRect(vStart, vEnd, SCOLOR, 0.0f, 240, 1.2f);
									
									auto tpColor = ImColor(255, 255, 255,30);
                                    auto bttomColor = ImColor(0, 175, 239, 30);
                                    auto tpoColor = ImColor(255, 0, 0,30);
                                    auto btotomColor = ImColor(255, 255, 255,30);
									draw->AddRectFilledMultiColor(vStart, vEnd, tpColor, tpoColor, btotomColor, bttomColor);
                            }
                            if (Config["ESP::HEALTH"]& Player->Health > 0) {
                                 
                                           int CurHP = (int) std::max(0, std::min(
                                                        (int) Player->Health,
                                                        (int) Player->HealthMax));
                                                int MaxHP = (int) Player->HealthMax;

                                            
														
												  long HPColor;
                                                
                                                       HPColor = SCOLOR;

                                                //if (Config.PlayerESP.ShowKnockedHealth) {
                                                if (Player->Health == 0.0f && !Player->bDead) {
													
													
													
                                                   
                                                    CurHP = Player->NearDeathBreath;
                                                    if (Player->NearDeatchComponent) {
                                                        MaxHP = Player->NearDeatchComponent->BreathMax;
                                                    }
                                                }
                                                //}

												if (Player->bIsAI) {
													
												SCOLOR = IM_COL32(20, 228, 134, 255);
                                                HPColor = IM_COL32(20, 228, 144, 90);

                                                float boxWidth = density / 1.6f;
                                                boxWidth -= std::min(
                                                        ((boxWidth / 2) / 0.001f) * Distance,
                                                        boxWidth / 2);
                                                float boxHeight = boxWidth * 0.15f;


                                                ImVec2 vStart = {HeadPosSC.x - (boxWidth / 2),
                                                                 HeadPosSC.y -
                                                                 (boxHeight * 2.001f)};

												
                                                ImVec2 vEndFilled = {
                                                        vStart.x + (CurHP * boxWidth / MaxHP),
                                                        vStart.y + boxHeight};
                                                ImVec2 vEndRect = {vStart.x + boxWidth,
                                                                   vStart.y + boxHeight};

                                                draw->AddRectFilled(vStart, vEndFilled, HPColor,
                                                                    10.0f);
                                                draw->AddRect(vStart, vEndRect,
                                                              SCOLOR, 10.0f);
															  
															    } else {
																	
												SCOLOR = IM_COL32(255, 0, 0, 255);
                                                HPColor = IM_COL32(255, 0, 20, 90);

                                                float boxWidth = density / 1.6f;
                                                boxWidth -= std::min(
                                                        ((boxWidth / 2) / 0.001f) * Distance,
                                                        boxWidth / 2);
                                                float boxHeight = boxWidth * 0.15f;


                                                ImVec2 vStart = {HeadPosSC.x - (boxWidth / 2),
                                                                 HeadPosSC.y -
                                                                 (boxHeight * 2.001f)};

												
                                                ImVec2 vEndFilled = {
                                                        vStart.x + (CurHP * boxWidth / MaxHP),
                                                        vStart.y + boxHeight};
                                                ImVec2 vEndRect = {vStart.x + boxWidth,
                                                                   vStart.y + boxHeight};

                                                draw->AddRectFilled(vStart, vEndFilled, HPColor,
                                                                    10.0f);
                                                draw->AddRect(vStart, vEndRect,
                                                              SCOLOR, 10.0f);
															  }
																	
                                }
                                      int NHK;
                            if (Config["ESP::TEAM_ID"]) {
                                        
                                std::string s;
                                s += "";
                                s += std::to_string(Player->TeamID);

  
				                 draw->AddText(NULL, ((float) density / 25.0f),
                                              {HeadPosSC.x - 60 , HeadPosSC.y - 38},
                                              IM_COL32(255, 255, 255, 250), s.c_str());
											  }
							
							if (Config["ESP::NAME"]) {

									
								   std::string s;
                                    if (Player->bIsAI) {
                                        s += "BOT";
                                     
                                    } else {
                                       s += "";
                                       s += Player->PlayerName.ToString();
                                    }
								    draw->AddText(NULL, 26, {HeadPosSC.x - 60, HeadPosSC.y - 73.5}, IM_COL32(255, 255, 255, 255), s.c_str());
                                    }
							
				


                    if (Config["ESP::DISTANCE"]) {
                                        std::string s;

                                    s += std::to_string((int) Distance);
                                    s += "M";

                                    draw->AddText(NULL, ((float) density / 25.0f), {HeadPosSC.x - 8, HeadPosSC.y - 22}, IM_COL32(255, 255, 255, 255), s.c_str());

									}
									}
									}
							
							

                     if (Config["ESP::VEHICLE"]) {
                        if (Actors[i]->IsA(ASTExtraVehicleBase::StaticClass())) {
                            auto Vehicle = (ASTExtraVehicleBase *) Actors[i];

                            if (!Vehicle->Mesh)
                                continue;

                            float Distance = Vehicle->GetDistanceTo(localPlayer) / 100.f;

                            FVector2D vehiclePos;
                            if (W2S(Vehicle->K2_GetActorLocation(), &vehiclePos)) {
                                std::string s = GetVehicleName(Vehicle);
                                s += " [";
                                s += std::to_string((int) Distance);
                                s += "m]";

                                draw->AddText(NULL, ((float) density / 30.0f),
                                              {vehiclePos.X, vehiclePos.Y},
                                              IM_COL32(255, 255, 000, 255), s.c_str());
                            }
                        }
                    }

					if (Config["ESP::WARNING"]) {
						if (Actors[i]->IsA(ASTExtraGrenadeBase::StaticClass())) {
							auto Grenade = (ASTExtraGrenadeBase *) Actors[i];
							auto RootComponent = Grenade->RootComponent;
							if (!RootComponent)
								continue;
							float Distance = Grenade->GetDistanceTo(localPlayer) / 70.f;
							FVector2D grenadePos;
							if (W2S(Grenade->K2_GetActorLocation(), & grenadePos)) {
								std::string s = std::to_string((int) Distance);
								s += " m";
								std::string t;
								t += "!!!...THROWABLE WARNING...!!!";
								auto textSize = ImGui::CalcTextSize2(t.c_str(), 0, ((float) density / 17.0f));
								draw->AddText(NULL, ((float) density / 17.0f), ImVec2(glWidth / 2 - (textSize.x / 2), 110), IM_COL32(255, 0, 0, 220), t.c_str());
								draw->AddText(NULL, ((float) density / 25.0f), {grenadePos.X - 10, grenadePos.Y - 10}, IM_COL32(255, 0, 0, 255), s.c_str());
							}
						}
					}
					if (Config["HACK::ENABLE"]) {
										draw->AddCircle(ImVec2(glWidth / 2, glHeight / 2), Config["FOV::SIZE"], IM_COL32(255, 0, 0, 255), 0, 2.0f);
						}
					
				
					
				if( Config["ESP::DEADBOX"]) {
                    if (Actors[i]->IsA(APickUpListWrapperActor::StaticClass())) {
                        auto Pick = (APickUpListWrapperActor *) Actors[i];
                        if (!Pick->RootComponent)
                            continue;
                        auto PickUpDataList = (TArray<FPickUpItemData>)Pick->GetDataList();
                        float Distance = Pick->GetDistanceTo(localPlayer) / 100.f;
                        FVector2D PickUpListsPos;
                        Vector3 origin, extends;
                        if (W2S(Pick->K2_GetActorLocation(), & PickUpListsPos)) {
                            std::string s = "LootBox";
                            s += " - ";
                            s += std::to_string((int) Distance);
                            s += "M";
                            draw->AddText(NULL, ((float) density / 20.0f), {PickUpListsPos.X, PickUpListsPos.Y}, IM_COL32(255, 215, 0, 255), s.c_str());
                            if (Config["ESP::DEADBOXITEMS"]) {
                                if (Distance <= 500.f) {
                                    auto mWidthScale = std::min(0.1f * Distance, 35.f);
                                    auto boxWidth = 75.f - mWidthScale;
                                    auto boxHeight = boxWidth * 0.120f;
                                    Rect PlayerRect(PickUpListsPos.X - (boxWidth / 2), PickUpListsPos.Y, boxWidth, boxHeight);
                                    float posY = PickUpListsPos.Y - (PlayerRect.height * 1.00f);
                                    for (int j = 0; j < PickUpDataList.Num(); j++) {
                                        std::vector<std::string> s2;
                                        std::string itm;
                                        uint32_t tc = 0xFF000000;
                                        for (auto & category : items_data) {
                                            for (auto & item : category["Items"]) {
                                                if (item["itemId"] == PickUpDataList[j].ID.TypeSpecificID) {
                                                    tc = strtoul(item["itemTextColor"].get<std::string>().c_str(), 0, 16);
                                                    itm += item["itemName"].get<std::string>();
                                                    s2.push_back(itm);
                                                    break;
                                                }
                                            }
                                        }
                                        if (!s2.empty())  {
                                            if (PickUpDataList[j].Count > 1) {
                                                s2.push_back(" * ");
                                                s2.push_back(std::to_string(PickUpDataList[j].Count));
                                            }
                                            std::string s3;
                                            for (auto & s4 : s2)   {
                                                s3 += s4;
                                            }
                                            draw->AddText(NULL, ((float) density / 22.0f), {PickUpListsPos.X, posY}, tc, s3.c_str());
                                            posY -= PlayerRect.height * 1.00f;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

					
                    if (Actors[i]->IsA(APickUpWrapperActor::StaticClass())) {
                        auto PickUp = (APickUpWrapperActor *) Actors[i];
                        if (Items[PickUp->DefineID.TypeSpecificID]) {
                            auto RootComponent = PickUp->RootComponent;
                            if (!RootComponent)
                                continue;

                            float Distance = PickUp->GetDistanceTo(localPlayer) / 100.f;

                            FVector2D itemPos;
                            if (W2S(PickUp->K2_GetActorLocation(), &itemPos)) {
                                std::string s;
                                uint32_t tc = 0xFF000000;

                                for (auto &category: items_data) {
                                    for (auto &item: category["Items"]) {
                                        if (item["itemId"] == PickUp->DefineID.TypeSpecificID) {
                                            s = item["itemName"].get<std::string>();
                                            tc = strtoul(
                                                    item["itemTextColor"].get<std::string>().c_str(),
                                                    0, 16);
                                            break;
                                        }
                                    }
                                }

                                s += " - ";
                                s += std::to_string((int) Distance);
                                s += "m";

                                draw->AddText(NULL, ((float) density / 25.0f),
                                              {itemPos.X, itemPos.Y}, tc, s.c_str());
                            }
                        }
                    }
                }
            }
        }
		
		
		

g_LocalController = localController;
         g_LocalPlayer = localPlayer;
	    if (EnimiesAlertNhk) {
		if (totalEnemies) {
        draw->AddText(NULL, ((float) density / 10.0f), {((float)glWidth / 2) - (glWidth / 8), 100}, ImColor(isRed, isBlue, isGreen), ICON_FA_EXCLAMATION_TRIANGLE"Warning! Enimes Alert");
        draw->AddText(NULL, ((float) density / 10.0f), {((float)glWidth / 2) - (glWidth / 8), 100}, ImColor(isRed, isBlue, isGreen), ICON_FA_EXCLAMATION_TRIANGLE"Warning! Enimes Alert");
        draw->AddText(NULL, ((float) density / 10.0f), {((float)glWidth / 2) - (glWidth / 8), 100}, ImColor(isRed, isBlue, isGreen), ICON_FA_EXCLAMATION_TRIANGLE"Warning! Enimes Alert");
        draw->AddText(NULL, ((float) density / 10.0f), {((float)glWidth / 2) - (glWidth / 8), 100}, ImColor(isRed, isBlue, isGreen), ICON_FA_EXCLAMATION_TRIANGLE"Warning! Enimes Alert");
       }
	}

        if (totalEnemies + totalBots > 0) {
            std::string s;
            if (totalEnemies + totalBots < 10)
                s += "     ";
            else s += "    ";
            s += std::to_string((int) totalEnemies + totalBots);
            draw->AddRectFilled(ImVec2(glWidth / 2 - 80, 50), ImVec2(glWidth / 2 + 80, 90), IM_COL32(227, 177, 39, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 72, 50), ImVec2(glWidth / 2 + 72, 90), IM_COL32(227, 177, 39, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 64, 50), ImVec2(glWidth / 2 + 64, 90), IM_COL32(227, 177, 39, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 60, 50), ImVec2(glWidth / 2 + 60, 90), IM_COL32(227, 177, 39, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 56, 50), ImVec2(glWidth / 2 + 56, 90), IM_COL32(227, 177, 39, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 52, 50), ImVec2(glWidth / 2 + 52, 90), IM_COL32(227, 177, 39, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 48, 50), ImVec2(glWidth / 2 + 48, 90), IM_COL32(227, 177, 39, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 44, 50), ImVec2(glWidth / 2 + 44, 90), IM_COL32(227, 177, 39, 38));
            draw->AddText(nullptr, ((float) density / 12.5f), ImVec2(glWidth / 2 - 50.f, 50), IM_COL32(1, 1, 1, 255), s.c_str());
        } else{
            std::string s;
            s += "CLEAR";
            draw->AddRectFilled(ImVec2(glWidth / 2 - 80, 50), ImVec2(glWidth / 2 + 80, 90), IM_COL32(0, 255, 0, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 72, 50), ImVec2(glWidth / 2 + 72, 90), IM_COL32(0, 255, 0, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 64, 50), ImVec2(glWidth / 2 + 64, 90), IM_COL32(0, 255, 0, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 60, 50), ImVec2(glWidth / 2 + 60, 90), IM_COL32(0, 255, 0, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 56, 50), ImVec2(glWidth / 2 + 56, 90), IM_COL32(0, 255, 0, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 52, 50), ImVec2(glWidth / 2 + 52, 90), IM_COL32(0, 255, 0, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 48, 50), ImVec2(glWidth / 2 + 48, 90), IM_COL32(0, 255, 0, 38));
            draw->AddRectFilled(ImVec2(glWidth / 2 - 44, 50), ImVec2(glWidth / 2 + 44, 90), IM_COL32(0, 255, 0, 38));
            draw->AddText(nullptr, ((float) density / 12.5f), ImVec2(glWidth / 2 - 50.f, 50), IM_COL32(1, 1, 1, 255), s.c_str());
        }
	
	
// ========  https://t.me/CHAPRI_VIP_MOD  ======= //
// ========  JOIN TELEGRAM  CHAPRI_VIP_MOD  =============== //
	
        fps.update();
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

    std::string getClipboardText() {
        if (!g_App)
            return "";

        auto activity = g_App->activity;
        if (!activity)
            return "";

        auto vm = activity->vm;
        if (!vm)
            return "";

        auto object = activity->clazz;
        if (!object)
            return "";

        std::string result;

        JNIEnv *env;
        vm->AttachCurrentThread(&env, 0);
        {
            auto ContextClass = env->FindClass("android/content/Context");
            auto getSystemServiceMethod = env->GetMethodID(ContextClass, "getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;");

            auto str = env->NewStringUTF("clipboard");
            auto clipboardManager = env->CallObjectMethod(object, getSystemServiceMethod, str);
            env->DeleteLocalRef(str);

            auto ClipboardManagerClass = env->FindClass("android/content/ClipboardManager");
            auto getText = env->GetMethodID(ClipboardManagerClass, "getText", "()Ljava/lang/CharSequence;");

            auto CharSequenceClass = env->FindClass("java/lang/CharSequence");
            auto toStringMethod = env->GetMethodID(CharSequenceClass, "toString", "()Ljava/lang/String;");

            auto text = env->CallObjectMethod(clipboardManager, getText);
            if (text) {
                str = (jstring) env->CallObjectMethod(text, toStringMethod);
                result = env->GetStringUTFChars(str, 0);
                env->DeleteLocalRef(str);
                env->DeleteLocalRef(text);
            }

            env->DeleteLocalRef(CharSequenceClass);
            env->DeleteLocalRef(ClipboardManagerClass);
            env->DeleteLocalRef(clipboardManager);
            env->DeleteLocalRef(ContextClass);
        }
        vm->DetachCurrentThread();

        return result;
    }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
	
    const char *GetAndroidID(JNIEnv *env, jobject context) {
        jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
        jmethodID getContentResolverMethod = env->GetMethodID(contextClass, /*getContentResolver*/ StrEnc("E8X\\7r7ys_Q%JS+L+~", "\x22\x5D\x2C\x1F\x58\x1C\x43\x1C\x1D\x2B\x03\x40\x39\x3C\x47\x3A\x4E\x0C", 18).c_str(), /*()Landroid/content/ContentResolver;*/ StrEnc("8^QKmj< }5D:9q7f.BXkef]A*GYLNg}B!/L", "\x10\x77\x1D\x2A\x03\x0E\x4E\x4F\x14\x51\x6B\x59\x56\x1F\x43\x03\x40\x36\x77\x28\x0A\x08\x29\x24\x44\x33\x0B\x29\x3D\x08\x11\x34\x44\x5D\x77", 35).c_str());
        jclass settingSecureClass = env->FindClass(/*android/provider/Settings$Secure*/ StrEnc("T1yw^BCF^af&dB_@Raf}\\FS,zT~L(3Z\"", "\x35\x5F\x1D\x05\x31\x2B\x27\x69\x2E\x13\x09\x50\x0D\x26\x3A\x32\x7D\x32\x03\x09\x28\x2F\x3D\x4B\x09\x70\x2D\x29\x4B\x46\x28\x47", 32).c_str());
        jmethodID getStringMethod = env->GetStaticMethodID(settingSecureClass, /*getString*/ StrEnc("e<F*J5c0Y", "\x02\x59\x32\x79\x3E\x47\x0A\x5E\x3E", 9).c_str(), /*(Landroid/content/ContentResolver;Ljava/lang/String;)Ljava/lang/String;*/ StrEnc("$6*%R*!XO\"m18o,0S!*`uI$IW)l_/_knSdlRiO1T`2sH|Ouy__^}%Y)JsQ:-\"(2_^-$i{?H", "\x0C\x7A\x4B\x4B\x36\x58\x4E\x31\x2B\x0D\x0E\x5E\x56\x1B\x49\x5E\x27\x0E\x69\x0F\x1B\x3D\x41\x27\x23\x7B\x09\x2C\x40\x33\x1D\x0B\x21\x5F\x20\x38\x08\x39\x50\x7B\x0C\x53\x1D\x2F\x53\x1C\x01\x0B\x36\x31\x39\x46\x0C\x15\x43\x2B\x05\x30\x15\x41\x43\x46\x55\x70\x0D\x59\x56\x00\x15\x58\x73", 71).c_str());

        auto obj = env->CallObjectMethod(context, getContentResolverMethod);
        auto str = (jstring) env->CallStaticObjectMethod(settingSecureClass, getStringMethod, obj, env->NewStringUTF(/*android_id*/ StrEnc("ujHO)8OfOE", "\x14\x04\x2C\x3D\x46\x51\x2B\x39\x26\x21", 10).c_str()));
        return env->GetStringUTFChars(str, 0);
    }

    const char *GetDeviceModel(JNIEnv *env) {
        jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("m5I{GKGWBP-VOxkA", "\x0C\x5B\x2D\x09\x28\x22\x23\x78\x2D\x23\x02\x14\x3A\x11\x07\x25", 16).c_str());
        jfieldID modelId = env->GetStaticFieldID(buildClass, /*MODEL*/ StrEnc("|}[q:", "\x31\x32\x1F\x34\x76", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());

        auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
        return env->GetStringUTFChars(str, 0);
    }

    const char *GetDeviceBrand(JNIEnv *env) {
        jclass buildClass = env->FindClass(/*android/os/Build*/ StrEnc("0iW=2^>0zTRB!B90", "\x51\x07\x33\x4F\x5D\x37\x5A\x1F\x15\x27\x7D\x00\x54\x2B\x55\x54", 16).c_str());
        jfieldID modelId = env->GetStaticFieldID(buildClass, /*BRAND*/ StrEnc("@{[FP", "\x02\x29\x1A\x08\x14", 5).c_str(), /*Ljava/lang/String;*/ StrEnc(".D:C:ETZ1O-Ib&^h.Y", "\x62\x2E\x5B\x35\x5B\x6A\x38\x3B\x5F\x28\x02\x1A\x16\x54\x37\x06\x49\x62", 18).c_str());

        auto str = (jstring) env->GetStaticObjectField(buildClass, modelId);
        return env->GetStringUTFChars(str, 0);
    }

    const char *GetPackageName(JNIEnv *env, jobject context) {
        jclass contextClass = env->FindClass(/*android/content/Context*/ StrEnc("`L+&0^[S+-:J^$,r9q92(as", "\x01\x22\x4F\x54\x5F\x37\x3F\x7C\x48\x42\x54\x3E\x3B\x4A\x58\x5D\x7A\x1E\x57\x46\x4D\x19\x07", 23).c_str());
        jmethodID getPackageNameId = env->GetMethodID(contextClass, /*getPackageName*/ StrEnc("YN4DaP)!{wRGN}", "\x3E\x2B\x40\x14\x00\x33\x42\x40\x1C\x12\x1C\x26\x23\x18", 14).c_str(), /*()Ljava/lang/String;*/ StrEnc("VnpibEspM(b]<s#[9cQD", "\x7E\x47\x3C\x03\x03\x33\x12\x5F\x21\x49\x0C\x3A\x13\x20\x57\x29\x50\x0D\x36\x7F", 20).c_str());

        auto str = (jstring) env->CallObjectMethod(context, getPackageNameId);
        return env->GetStringUTFChars(str, 0);
    }

    const char *GetDeviceUniqueIdentifier(JNIEnv *env, const char *uuid) {
        jclass uuidClass = env->FindClass(/*java/util/UUID*/ StrEnc("B/TxJ=3BZ_]SFx", "\x28\x4E\x22\x19\x65\x48\x47\x2B\x36\x70\x08\x06\x0F\x3C", 14).c_str());

        auto len = strlen(uuid);

        jbyteArray myJByteArray = env->NewByteArray(len);
        env->SetByteArrayRegion(myJByteArray, 0, len, (jbyte *) uuid);

        jmethodID nameUUIDFromBytesMethod = env->GetStaticMethodID(uuidClass, /*nameUUIDFromBytes*/ StrEnc("P6LV|'0#A+zQmoat,", "\x3E\x57\x21\x33\x29\x72\x79\x67\x07\x59\x15\x3C\x2F\x16\x15\x11\x5F", 17).c_str(), /*([B)Ljava/util/UUID;*/ StrEnc("sW[\"Q[W3,7@H.vT0) xB", "\x5B\x0C\x19\x0B\x1D\x31\x36\x45\x4D\x18\x35\x3C\x47\x1A\x7B\x65\x7C\x69\x3C\x79", 20).c_str());
        jmethodID toStringMethod = env->GetMethodID(uuidClass, /*toString*/ StrEnc("2~5292eW", "\x46\x11\x66\x46\x4B\x5B\x0B\x30", 8).c_str(), /*()Ljava/lang/String;*/ StrEnc("P$BMc' #j?<:myTh_*h0", "\x78\x0D\x0E\x27\x02\x51\x41\x0C\x06\x5E\x52\x5D\x42\x2A\x20\x1A\x36\x44\x0F\x0B", 20).c_str());

        auto obj = env->CallStaticObjectMethod(uuidClass, nameUUIDFromBytesMethod, myJByteArray);
        auto str = (jstring) env->CallObjectMethod(obj, toStringMethod);
        return env->GetStringUTFChars(str, 0);
    }

    struct MemoryStruct {
        char *memory;
        size_t size;
    };

    static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp) {
        size_t realsize = size * nmemb;
        struct MemoryStruct *mem = (struct MemoryStruct *) userp;

        mem->memory = (char *) realloc(mem->memory, mem->size + realsize + 1);
        if (mem->memory == NULL) {
            return 0;
        }

        memcpy(&(mem->memory[mem->size]), contents, realsize);
        mem->size += realsize;
        mem->memory[mem->size] = 0;

        return realsize;
    }

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
	
    EGLBoolean (*orig_eglSwapBuffers)(EGLDisplay dpy, EGLSurface surface);

    EGLBoolean _eglSwapBuffers(EGLDisplay dpy, EGLSurface surface) {
        eglQuerySurface(dpy, surface, EGL_WIDTH, &glWidth);
        eglQuerySurface(dpy, surface, EGL_HEIGHT, &glHeight);
        if (glWidth <= 0 || glHeight <= 0)
            return orig_eglSwapBuffers(dpy, surface);

        if (!g_App)
            return orig_eglSwapBuffers(dpy, surface);

        screenWidth = ANativeWindow_getWidth(g_App->window);
        screenHeight = ANativeWindow_getHeight(g_App->window);
        density = AConfiguration_getDensity(g_App->config);

        if (!initImGui) {
                  ImGui::CreateContext();

            ImGuiStyle *style = &ImGui::GetStyle();
                   
        style->Colors[ImGuiCol_Text]                  = ImColor(255, 255, 255, 255);
	    style->Colors[ImGuiCol_WindowBg]              = ImColor(0, 0, 0, 255);
        style->Colors[ImGuiCol_FrameBg]               = ImColor(219, 20, 61, 255);
		style->Colors[ImGuiCol_FrameBgActive]               = ImColor(219, 20, 61, 255);
		style->Colors[ImGuiCol_FrameBgHovered]               = ImColor(219, 20, 61, 255);
	    style->Colors[ImGuiCol_PopupBg]               = ImColor(77, 37, 46, 255);
		style->Colors[ImGuiCol_Button]                   = ImColor(219, 20, 61, 255);
		style->Colors[ImGuiCol_ButtonActive]             = ImColor(219, 20, 61, 255);
		style->Colors[ImGuiCol_ButtonHovered]            = ImColor(219, 20, 61, 255);
        style->Colors[ImGuiCol_TitleBg]               = ImColor(77, 37, 46, 255);
        style->Colors[ImGuiCol_TitleBgActive]         = ImColor(77, 37, 46, 255);
        style->Colors[ImGuiCol_TitleBgCollapsed]      = ImColor(77, 37, 46, 255);
	    style->Colors[ImGuiCol_CheckMark]             = ImColor(255, 255, 255, 255);
        ImGui_ImplAndroid_Init();
        ImGui_ImplOpenGL3_Init("#version 300 es");

            ImGuiIO &io = ImGui::GetIO();

            io.ConfigWindowsMoveFromTitleBarOnly = true;
            io.IniFilename = NULL;

            static const ImWchar icons_ranges[] = { 0xf000, 0xf3ff, 0 };
            ImFontConfig icons_config;

            ImFontConfig CustomFont;
            CustomFont.FontDataOwnedByAtlas = false;

            icons_config.MergeMode = true;
            icons_config.PixelSnapH = true;
            icons_config.OversampleH = 2.5;
            icons_config.OversampleV = 2.5;
            
          io.Fonts->AddFontFromMemoryTTF((void *)BaiduZY_data, BaiduZY_size, 25.0f, NULL, io.Fonts->GetGlyphRangesChineseFull());
		  io.Fonts->AddFontFromMemoryCompressedTTF(font_awesome_data, font_awesome_size, 28.0f, &icons_config, icons_ranges);
		  io.Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(Custom), sizeof(Custom), 24.f, &CustomFont);
          memset(&Demon, 0, sizeof(sDemon));
// ===============================ESPCOLOR ================================== //


        Demon.ColorsESP.Line = CREATE_COLOR(255, 0, 0, 255);
        Demon.ColorsESP.Box = CREATE_COLOR(255, 0, 0, 255);
        Demon.ColorsESP.Name = CREATE_COLOR(255, 255, 255, 255);
        Demon.ColorsESP.Skeleton = CREATE_COLOR(255, 0, 0, 255);
        Demon.ColorsESP.Vehicle = CREATE_COLOR(255, 255, 255, 255);
        Demon.ColorsESP.SkeletonVisible = CREATE_COLOR(0, 255, 0, 255);
        initImGui = true;
    }

    ImGuiIO &io = ImGui::GetIO();
	
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplAndroid_NewFrame(glWidth, glHeight);
    ImGui::NewFrame();

    DrawESP(ImGui::GetBackgroundDrawList());
	
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\

// @JAGDISH_VIP // DEVELOPER // JAGDISH PAPA

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\\
	
        ImGui::End();
    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return orig_eglSwapBuffers(dpy, surface);
}

    int32_t (*orig_onInputEvent)(struct android_app *app, AInputEvent *inputEvent);

    int32_t onInputEvent(struct android_app *app, AInputEvent *inputEvent) {
        if (initImGui) {
            ImGui_ImplAndroid_HandleInputEvent(inputEvent, {(float) screenWidth / (float) glWidth, (float) screenHeight / (float) glHeight});
        }
        return orig_onInputEvent(app, inputEvent);
    }
	
void native_onSendConfig(JNIEnv *env, jobject thiz, jstring s, jstring v) {
    const char *config = env->GetStringUTFChars(s, 0);
    const char *value = env->GetStringUTFChars(v, 0);

    if (!strcmp(config, "CMD_PARSE_ITEMS")) {
        itemData = json::parse(value);
    } else if (!strcmp(config, "ESP::ITEMS")) {
        u_long itemId = strtoul(value, 0, 0);
        itemConfig[itemId] = !itemConfig[itemId];
    } else {
        Config[config] = (u_long) strtoul(value, 0, 0);
    }
}

#define SLEEP_TIME 1000LL / 60LL

    [[noreturn]] void *maps_thread(void *) {
        while (true) {
            auto t1 = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();

            std::vector<sRegion> tmp;
            char line[512];
            FILE *f = fopen("/proc/self/maps", "r");
            if (f) {
                while (fgets(line, sizeof line, f)) {
                    uintptr_t start, end;
                    char tmpProt[16];
                    if (sscanf(line, "%" PRIXPTR "-%" PRIXPTR " %16s %*s %*s %*s %*s", &start, &end, tmpProt) > 0) {
                        if (tmpProt[0] != 'r') {
                            tmp.push_back({start, end});
                        }
                    }
                }
                fclose(f);
            }
            trapRegions = tmp;

            auto td = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count() - t1;
            std::this_thread::sleep_for(std::chrono::milliseconds(std::max(std::min(0LL, SLEEP_TIME - td), SLEEP_TIME)));
        }
    }
    int (*osub_1B40B4)(const char *a1, unsigned int a2);
int hsub_1B40B4(const char *a1, unsigned int a2)
{
    while(true)
    {
        sleep(10000);
    }
    return osub_1B40B4(a1,a2);
}
int (*ret_Zero)();
int Hooked_Ret_Zero() {
    return 0;
      }
void *Super_thread(void *) 
{
 ProcMap libanogs; 
do 
{ libanogs = KittyMemory::getLibraryMap("libanogs.so");
  sleep(1);
} while(!libanogs.isValid());
MemoryPatch::createWithHex(OBFUSCATE("libanogs.so"),  0x8c168, OBFUSCATE("00 00 00 00 74 DE 3E 88")).Modify();



ProcMap libUE4; 
do 
{ libUE4 = KittyMemory::getLibraryMap("libUE4.so");
  sleep(1);
} while(!libUE4.isValid());
//PATCH_LIB("libUE4.so", "0xA0E8C", "C0 03 5F D6");


ProcMap libanort; 
do 
{ libanort = KittyMemory::getLibraryMap("libanort.so");
  sleep(1);
} while(!libanort.isValid());
//PATCH_LIB("libanort.so", "0x2AB0C", "C0 03 5F D6");
HOOK_LIB("libanort.so", "0x1B40B4", hsub_1B40B4, osub_1B40B4);

ProcMap libhdmpve; 
do 
{ libhdmpve = KittyMemory::getLibraryMap("libhdmpve.so");
  sleep(1);
} while(!libhdmpve.isValid());
//PATCH_LIB("libhdmpve.so", "0x3CB34C", "C0 03 5F D6");


 return NULL;
 }
    
    void *main_thread(void *) {
		
		if (Config["MAGIC::BULLET"]) {
   kFox::SetSearchRange(RegionType::ANONYMOUS);
   kFox::MemorySearch("25", Type::TYPE_FLOAT);
   kFox::MemoryOffset("30.5", 4, Type::TYPE_FLOAT);
   kFox::MemoryWrite("900", 0, Type::TYPE_FLOAT);
   kFox::MemoryWrite("900", 4, Type::TYPE_FLOAT);
   kFox::ClearResult();

   kFox::SetSearchRange(RegionType::ANONYMOUS);
   kFox::MemorySearch("69.5", Type::TYPE_FLOAT);
   kFox::MemoryOffset("33.0", -4, Type::TYPE_FLOAT);
   kFox::MemoryOffset("35.0", -8, Type::TYPE_FLOAT);
   kFox::MemoryWrite("89.5", 0, Type::TYPE_FLOAT);
	          }
		
        UE4 = Tools::GetBaseAddress("libUE4.so");
        while (!UE4) {
            UE4 = Tools::GetBaseAddress("libUE4.so");
            sleep(1);
        }
        anogs = Tools::GetBaseAddress("libanogs.so");
        while (!anogs) {
            UE4 = Tools::GetBaseAddress("libanogs.so");
            sleep(1);
        }
		anort = Tools::GetBaseAddress("libanort.so");
        while (!anort) {
            anort = Tools::GetBaseAddress("libanort.so");
            sleep(1);
        }
		AntsVoice = Tools::GetBaseAddress("libAntsVoice.so");
        while (!AntsVoice) {
            AntsVoice = Tools::GetBaseAddress("libAntsVoice.so");
            sleep(1);
        }
         hdmpve = Tools::GetBaseAddress("libhdmpve.so");
        while (!hdmpve) {
            hdmpve = Tools::GetBaseAddress("libhdmpve.so");
            sleep(1);
        }

        while (!g_App) {
            g_App = *(android_app **) (UE4 + GNativeAndroidApp_Offset);
            sleep(1);
        }

        while (!g_App->onInputEvent)
            sleep(1);

        orig_onInputEvent = decltype(orig_onInputEvent)(g_App->onInputEvent);
        g_App->onInputEvent = onInputEvent;

        FName::GNames = GetGNames();
        while (!FName::GNames) {
            FName::GNames = GetGNames();
            sleep(1);
        }
        UObject::GUObjectArray = (FUObjectArray *) (UE4 + GUObject_Offset);

        void *egl = dlopen_ex("libEGL.so", 4);
        while (!egl) {
            egl = dlopen_ex("libEGL.so", 4);
            sleep(1);
        }

        void *addr = dlsym_ex(egl, "eglSwapBuffers");
        HOOK(addr, _eglSwapBuffers, &orig_eglSwapBuffers);
        dlclose_ex(egl);

        pthread_t t;
        pthread_create(&t, 0, maps_thread, 0);
		pthread_create(&t, 0, Super_thread, 0);

        items_data = json::parse(JSON_ITEMS);

        return 0;
    }

    jstring native_Check(JNIEnv *env, jclass clazz, jobject jContext, jstring jUserKey) {
    auto userKey = env->GetStringUTFChars(jUserKey, 0);

    std::string hwid = userKey;
    hwid += GetAndroidID(env, jContext);
    hwid += GetDeviceModel(env);
    hwid += GetDeviceBrand(env);

    std::string UUID = GetDeviceUniqueIdentifier(env, hwid.c_str());

    std::string errMsg;

    struct MemoryStruct chunk{};
    chunk.memory = (char *) malloc(1);
    chunk.size = 0;

    CURL *curl;
    CURLcode res;
    curl = curl_easy_init();
    if (curl) {
        std::string BHATIA = OBFUSCATE ("https://vipkey.in/public/connect");
        curl_easy_setopt(curl, CURLOPT_URL ,BHATIA.c_str());

        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, /*https*/ StrEnc("!mLBO", "\x49\x19\x38\x32\x3C", 5).c_str());
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, /*Content-Type: application/x-www-form-urlencoded*/ StrEnc("@;Ls\\(KP4Qrop`b#d3094/r1cf<c<=H)AiiBG6i|Ta66s2[", "\x03\x54\x22\x07\x39\x46\x3F\x7D\x60\x28\x02\x0A\x4A\x40\x03\x53\x14\x5F\x59\x5A\x55\x5B\x1B\x5E\x0D\x49\x44\x4E\x4B\x4A\x3F\x04\x27\x06\x1B\x2F\x6A\x43\x1B\x10\x31\x0F\x55\x59\x17\x57\x3F", 47).c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        char data[4096];
        sprintf(data, /*game=PUBG&user_key=%s&serial=%s*/ StrEnc("qu2yXK,YkJyGD@ut0.u~Nb'5(:.:chK", "\x16\x14\x5F\x1C\x65\x1B\x79\x1B\x2C\x6C\x0C\x34\x21\x32\x2A\x1F\x55\x57\x48\x5B\x3D\x44\x54\x50\x5A\x53\x4F\x56\x5E\x4D\x38", 31).c_str(), userKey, UUID.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) &chunk);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);
        if (res == CURLE_OK) {
            try {
                json result = json::parse(chunk.memory);
                if (result[/*status*/ StrEnc("(>_LBm", "\x5B\x4A\x3E\x38\x37\x1E", 6).c_str()] == true) {
                    std::string token = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*token*/ StrEnc("{>3Lr", "\x0F\x51\x58\x29\x1C", 5).c_str()].get<std::string>();
                    time_t rng = result[/*data*/ StrEnc("fAVA", "\x02\x20\x22\x20", 4).c_str()][/*rng*/ StrEnc("+n,", "\x59\x00\x4B", 3).c_str()].get<time_t>();
				      // BHATIA_EXP = result["data"]["BHATIA_EXP"].get<std::string>();
                      //  BHATIA_SLOT = result["data"]["BHATIA_SLOT"].get<std::string>();
                    //    ModName64 = result["data"]["ModName64"].get<std::string>();
                     //   MOD_STATUS64 = result["data"]["MOD_STATUS64"].get<std::string>();
                      //  FLOTING_TEST64 = result["data"]["FLOTING_TEST64"].get<std::string>();
				BHATIA_EXP = "23-09-2024";
				BHATIA_SLOT = "23T";
				ModName64 = "Kunal Khanna";
				MOD_STATUS64 = "Working";
				FLOTING_TEST64="Tested";
                    
					if (rng + 30 > time(0)) {
                        std::string auth = /*PUBG*/ StrEnc("Q*) ", "\x01\x7F\x6B\x67", 4).c_str();;
                        auth += "-";
                        auth += userKey;
                        auth += "-";
                        auth += UUID;
                        auth += "-";
                        auth += /*Vm8Lk7Uj2JmsjCPVPVjrLa7zgfx3uz9E*/ StrEnc("ZD$_K NtaM8Fu=n0fFyO;!Ae<H)*Gy4%", "\x0C\x29\x1C\x13\x20\x17\x1B\x1E\x53\x07\x55\x35\x1F\x7E\x3E\x66\x36\x10\x13\x3D\x77\x40\x76\x1F\x5B\x2E\x51\x19\x32\x03\x0D\x60", 32).c_str();;;
                        std::string outputAuth = Tools::CalcMD5(auth);

                        g_Token = token;
                        g_Auth = outputAuth;

                        bValid = g_Token == g_Auth;

                        if (bValid) {
                        static std::string keyop = OBFUSCATE("THUNDER-30D-HRHC040TE5QI");
                        static std::string panel = OBFUSCATE("https://api.fyu46.tk/thunder/login.php");
                        strcpy(chars, keyop.c_str());
                        strcpy(dword, panel.c_str());
							
                        pthread_t t;
                        pthread_create(&t, 0, main_thread, 0);
                        }
                    }
                } else {
                    errMsg = result[/*reason*/ StrEnc("LW(3(c", "\x3E\x32\x49\x40\x47\x0D", 6).c_str()].get<std::string>();
                }
            } catch (json::exception &e) {
                errMsg = e.what();
            }
        } else {
            errMsg = curl_easy_strerror(res);
        }
    }
    curl_easy_cleanup(curl);
    return bValid ? env->NewStringUTF(/*OK*/ StrEnc("8q", "\x77\x3A", 2).c_str()) : env->NewStringUTF(errMsg.c_str());
}


int Register3(JNIEnv *env) {
    JNINativeMethod methods[] = {{"onSendConfig", "(Ljava/lang/String;Ljava/lang/String;)V", (void *) native_onSendConfig}};
    jclass clazz = env->FindClass("com/justinhuman/bullet");
    if (!clazz)
        return -1;
    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return -1;
    return 0;
}
int Register2(JNIEnv *env) {
    JNINativeMethod methods[] = {{"Check", "(Landroid/content/Context;Ljava/lang/String;)Ljava/lang/String;", (void *) native_Check}};

    jclass clazz = env->FindClass("com/justinhuman/Launcher");
    if (!clazz)
        return -1;

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return -1;

    return 0;
}


jclass (*orig_FindClass)(JNIEnv *env, const char *name);
int Register1(JNIEnv *env) {
    JNINativeMethod methods[] = {{"onSendConfig", "(Ljava/lang/String;Ljava/lang/String;)V", (void *) native_onSendConfig}};


    jclass clazz = env->FindClass("com/justinhuman/Floating");
    if (!clazz)
        return -1;

    if (env->RegisterNatives(clazz, methods, sizeof(methods) / sizeof(methods[0])) != 0)
        return -1;

    return 0;
}
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env;
    vm->GetEnv((void **) &env, JNI_VERSION_1_6);

    if (Register1(env) != 0)
        return -1;

    if (Register2(env) != 0)
        return -1;
		
	if (Register3(env) != 0)
        return -1;

    return JNI_VERSION_1_6;
}
 extern "C" JNIEXPORT jstring JNICALL
Java_com_justinhuman_Launcher_chars(JNIEnv *env, jobject activityObject) {

    return env->NewStringUTF(chars);    
 }     
 
 extern "C" JNIEXPORT jstring JNICALL
Java_com_justinhuman_FloatIcon_dword(JNIEnv *env, jobject activityObject) {

    return env->NewStringUTF(dword);    
 }     
 

 extern "C" JNIEXPORT jstring JNICALL
Java_com_justinhuman_Floating_MODNAME(JNIEnv *env, jobject thiz) {
    return env->NewStringUTF(ModName64.c_str());   
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_justinhuman_Floating_keyexe(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF(BHATIA_EXP.c_str());
}
extern "C" JNIEXPORT jstring JNICALL
Java_com_justinhuman_Floating_SLOT(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF(FLOTING_TEST64.c_str());
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_justinhuman_Floating_keyexe22(JNIEnv *env, jobject activityObject) {
    return env->NewStringUTF(OBFUSCATE("Expiry:"));
}
