/// @file

// OPENGL:
#define INTEROP       true                                                                          // "true" = use OpenGL-OpenCL interoperability.
#define GUI_SIZE_X    800                                                                           // Window x-size [px].
#define GUI_SIZE_Y    600                                                                           // Window y-size [px].
#define GUI_NAME      "Neutrino - Mesh"                                                             // Window name.

#ifdef __linux__
  #define SHADER_HOME "../Mesh/Code/shader"                                                         // Linux OpenGL shaders directory.
  #define KERNEL_HOME "../Mesh/Code/kernel"                                                         // Linux OpenCL kernels directory.
  #define GMHS_HOME   "../Mesh/Code/mesh/"                                                          // Linux GMSH mesh directory.
#endif

#ifdef __APPLE__
  #define SHADER_HOME "../Mesh/Code/shader"                                                         // Mac OpenGL shaders directory.
  #define KERNEL_HOME "../Mesh/Code/kernel"                                                         // Mac OpenCL kernels directory.
  #define GMHS_HOME   "../Mesh/Code/mesh/"                                                          // Mac GMSH mesh directory.
#endif

#ifdef WIN32
  #define SHADER_HOME "..\\..\\Mesh\\Code\\shader"                                                  // Windows OpenGL shaders directory.
  #define KERNEL_HOME "..\\..\\Mesh\\Code\\kernel"                                                  // Windows OpenCL kernels directory.
  #define GMHS_HOME   "..\\..\\Mesh\\Code\\mesh\\"                                                  // Windows GMSH mesh directory.
#endif

#define SHADER_VERT   "voxel_vertex.vert"                                                           // OpenGL vertex shader.
#define SHADER_GEOM   "voxel_geometry.geom"                                                         // OpenGL geometry shader.
#define SHADER_FRAG   "voxel_fragment.frag"                                                         // OpenGL fragment shader.
#define GMHS_MESH     "Utah_teapot.msh"                                                             // GMSH mesh.

// OPENCL:
#define QUEUE_NUM     1                                                                             // # of OpenCL queues [#].
#define KERNEL_NUM    1                                                                             // # of OpenCL kernel [#].

// INCLUDES:
#include "nu.hpp"                                                                                   // Neutrino's header file.

int main ()
{
  // KERNEL FILES:
  std::string              kernel_home;                                                             // Kernel home directory.
  std::vector<std::string> kernel_file;                                                             // Kernel source file.

  // DATA:
  float                    x_min              = -1.0;                                               // "x_min" spatial boundary [m].
  float                    x_max              = +1.0;                                               // "x_max" spatial boundary [m].
  float                    y_min              = -1.0;                                               // "y_min" spatial boundary [m].
  float                    y_max              = +1.0;                                               // "y_max" spatial boundary [m].
  size_t                   gid;                                                                     // Global index [#].

  // GUI PARAMETERS (orbit):
  float                    orbit_x_init       = 0.0f;                                               // x-axis orbit initial rotation.
  float                    orbit_y_init       = 0.0f;                                               // y-axis orbit initial rotation.

  // GUI PARAMETERS (pan):
  float                    pan_x_init         = 0.0f;                                               // x-axis pan initial translation.
  float                    pan_y_init         = 0.0f;                                               // y-axis pan initial translation.
  float                    pan_z_init         = -2.0f;                                              // z-axis pan initial translation.

  // GUI PARAMETERS (mouse):
  float                    mouse_orbit_rate   = 1.0;                                                // Orbit rotation rate [rev/s].
  float                    mouse_pan_rate     = 5.0;                                                // Pan translation rate [m/s].
  float                    mouse_decaytime    = 1.25;                                               // Pan LP filter decay time [s].

  // GUI PARAMETERS (gamepad):
  float                    gamepad_orbit_rate = 1.0;                                                // Orbit angular rate coefficient [rev/s].
  float                    gamepad_pan_rate   = 1.0;                                                // Pan translation rate [m/s].
  float                    gamepad_decaytime  = 1.25;                                               // Low pass filter decay time [s].
  float                    gamepad_deadzone   = 0.1;                                                // Gamepad joystick deadzone [0...1].

  // NEUTRINO:
  neutrino*                bas                = new neutrino ();                                    // Neutrino baseline.
  opengl*                  gui                = new opengl ();                                      // OpenGL context.
  opencl*                  ctx                = new opencl ();                                      // OpenCL context.
  shader*                  S                  = new shader ();                                      // OpenGL shader program.
  queue*                   Q                  = new queue ();                                       // OpenCL queue.
  kernel*                  K1                 = new kernel ();                                      // OpenCL kernel array.
  size_t                   kernel_sx;                                                               // Kernel dimension "x" [#].
  size_t                   kernel_sy;                                                               // Kernel dimension "y" [#].
  size_t                   kernel_sz;                                                               // Kernel dimension "z" [#].

  // MESH:
  mesh*                    object             = new mesh ();                                        // Mesh object.                                                                                // Total # of nodes [#].

  // NODE KINEMATICS:
  float4G*                 node               = new float4G ();                                     // Position [m].
  float4G*                 color              = new float4G ();                                     // Depth [m].
  int1*                    simplex            = new int1 ();                                        // Simplex: node index list.
  int1*                    simplex_stride     = new int1 ();                                        // Simplex: strides.
  int1*                    complex            = new int1 ();                                        // Complex: simplex index list.
  int1*                    complex_stride     = new int1 ();                                        // Complex: strides.

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////// DATA INITIALIZATION //////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  object->init (bas, std::string (GMHS_HOME) + std::string (GMHS_MESH));                            // Initializing cloth mesh...
  node->init (object->node[0].size ());                                                             // Initializing position data...
  color->init (object->node[0].size ());                                                            // Initializing depth data...
  simplex->init (object->simplex[0][0].size ());

  std::cout << "Number of nodes = " << object->node[0].size () << std::endl;
  std::cout << "Number of simplexes = " << object->simplex[0][0].size () << std::endl;

  node->name  = "voxel_center";                                                                     // Setting variable name for OpenGL shader...
  color->name = "voxel_color";                                                                      // Setting variable name for OpenGL shader...

  for(gid = 0; gid < object->simplex[0][0].size (); gid++)
  {
    std::cout << "Simplex " << gid << ": vertexes = ";

    for(int i = 0; i < object->simplex[0][0][gid].vertex.size (); i++)
    {
      std::cout << object->simplex[0][0][gid].vertex[i] << " ";
    }

    std::cout << std::endl;
  }

  std::cout << std::endl;

  for(gid = 0; gid < object->node[0].size (); gid++)
  {
    std::cout << "Complex " << gid << ": simplexes = ";

    for(int i = 0; i < object->complex[0][gid].size (); i++)
    {
      std::cout << object->complex[0][gid][i] << " ";
    }

    std::cout << std::endl;
  }

  for(gid = 0; gid < object->node[0].size (); gid++)
  {
    node->data[gid].x  = object->node[0][gid].x;
    node->data[gid].y  = object->node[0][gid].y;
    node->data[gid].z  = object->node[0][gid].z;
    node->data[gid].w  = object->node[0][gid].w;

    color->data[gid].x = 0.01f*(rand () % 100);                                                     // Setting "r" color coordinate...
    color->data[gid].y = 0.01f*(rand () % 100);                                                     // Setting "g" color coordinate...
    color->data[gid].z = 0.01f*(rand () % 100);                                                     // Setting "b" color coordinate...
    color->data[gid].w = 1.0f;                                                                      // Setting "a" color coordinate...
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////// NEUTRINO INITIALIZATION /////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  bas->init (QUEUE_NUM, KERNEL_NUM);                                                                // Initializing Neutrino baseline...
  gui->init                                                                                         // Initializing Neutrino GUI...
  (
   bas,                                                                                             // Neutrino baseline.
   GUI_SIZE_X,                                                                                      // GUI x-size [px].
   GUI_SIZE_Y,                                                                                      // GUI y-size [px.]
   GUI_NAME,                                                                                        // GUI name.
   orbit_x_init,                                                                                    // Initial x-orbit.
   orbit_y_init,                                                                                    // Initial y-orbit.
   pan_x_init,                                                                                      // Initial x-pan.
   pan_y_init,                                                                                      // Initial y-pan.
   pan_z_init                                                                                       // Initial z-pan.
  );
  ctx->init (bas, gui, NU_GPU);                                                                     // Initializing OpenCL context...
  S->init (bas, SHADER_HOME, SHADER_VERT, SHADER_GEOM, SHADER_FRAG);                                // Initializing OpenGL shader...
  Q->init (bas);                                                                                    // Initializing OpenCL queue...

  kernel_sx   = object->node[0].size ();                                                            // Kernel dimension "x" [#].
  kernel_sy   = 0;                                                                                  // Kernel dimension "y" [#].
  kernel_sz   = 0;                                                                                  // Kernel dimension "z" [#].

  kernel_home = KERNEL_HOME;                                                                        // Setting kernel home directory...
  kernel_file.push_back ("mesh_kernel.cl");                                                         // Setting 1st source file...
  K1->init (bas, kernel_home, kernel_file, kernel_sx, kernel_sy, kernel_sz);                        // Initializing OpenCL kernel K1...

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////// SETTING OPENCL KERNEL ARGUMENTS /////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  K1->setarg (node, 0);                                                                             // Setting position kernel argument...
  K1->setarg (color, 1);                                                                            // Setting depth kernel argument...

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////// WRITING DATA ON OPENCL QUEUE //////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  Q->write (node, 0);                                                                               // Writing position data on queue...
  Q->write (color, 1);                                                                              // Writing depth data on queue...

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////// SETTING OPENGL SHADER ARGUMENTS ////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  S->setarg (node, 0);                                                                              // Setting shader argument "0"...
  S->setarg (color, 1);                                                                             // Setting shader argument "1"...
  S->build ();                                                                                      // Building shader program...

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  ////////////////////////////////////////// APPLICATION LOOP ////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  while(!gui->closed ())                                                                            // Opening window...
  {
    bas->get_tic ();                                                                                // Getting "tic" [us]...

    gui->clear ();                                                                                  // Clearing gui...
    gui->poll_events ();                                                                            // Polling gui events...

    Q->acquire (node, 0);                                                                           // Acquiring OpenGL/CL shared argument...
    Q->acquire (color, 1);                                                                          // Acquiring OpenGL/CL shared argument...
    ctx->execute (K1, Q, NU_WAIT);                                                                  // Executing OpenCL kernel...
    Q->release (node, 0);                                                                           // Releasing OpenGL/CL shared argument...
    Q->release (color, 1);                                                                          // Releasing OpenGL/CL shared argument...

    gui->mouse_navigation (
                           mouse_orbit_rate,                                                        // Orbit angular rate coefficient [rev/s].
                           mouse_pan_rate,                                                          // Pan translation rate [m/s].
                           mouse_decaytime                                                          // Orbit low pass decay time [s].
                          );

    gui->gamepad_navigation (
                             gamepad_orbit_rate,                                                    // Orbit angular rate coefficient [rev/s].
                             gamepad_pan_rate,                                                      // Pan translation rate [m/s].
                             gamepad_decaytime,                                                     // Low pass filter decay time [s].
                             gamepad_deadzone                                                       // Gamepad joystick deadzone [0...1].
                            );

    if(gui->button_CROSS)
    {
      gui->close ();                                                                                // Closing gui...
    }

    gui->plot (S);                                                                                  // Plotting shared arguments...
    gui->refresh ();                                                                                // Refreshing gui...
    bas->get_toc ();                                                                                // Getting "toc" [us]...
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////// CLEANUP ////////////////////////////////////////////
  ////////////////////////////////////////////////////////////////////////////////////////////////////
  delete bas;                                                                                       // Deleting Neutrino baseline...
  delete gui;                                                                                       // Deleting OpenGL gui...
  delete ctx;                                                                                       // Deleting OpenCL context...

  delete object;                                                                                    // Deleting object data...
  delete node;                                                                                      // Deleting position data...
  delete color;                                                                                     // Deleting depth data...

  delete Q;                                                                                         // Deleting OpenCL queue...
  delete K1;                                                                                        // Deleting OpenCL kernel...

  return 0;
}
