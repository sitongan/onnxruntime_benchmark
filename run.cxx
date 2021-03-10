#include <onnxruntime_cxx_api.h>
#include <iostream>
#include <chrono>


int main(){

   const int batchsize = 64;

   Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "test");
   Ort::SessionOptions session_options;
   session_options.SetIntraOpNumThreads(1);
   session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

   const char* model_path = "Linear_64.onnx";

   printf("Using Onnxruntime C++ API\n");
   Ort::AllocatorWithDefaultOptions allocator;
   Ort::Session session(env, model_path, session_options);
   std::vector<const char*> input_node_names(1);
   std::vector<const char*> output_node_names(1);
   input_node_names[0] = session.GetInputName(0, allocator);
   output_node_names[0] = session.GetOutputName(0, allocator);
   Ort::TypeInfo type_info = session.GetInputTypeInfo(0);
   auto tensor_info = type_info.GetTensorTypeAndShapeInfo();
   std::vector<int64_t> input_node_dims = tensor_info.GetShape();
   std::cout << "input size: ";
   for (auto &i: input_node_dims){
      std::cout << i << ",";
   }
   std::cout <<std::endl;

   size_t input_tensor_size = batchsize*100;
   std::vector<float> input_tensor_values(input_tensor_size);

   for (unsigned int i = 0; i < input_tensor_size; i++)
    input_tensor_values[i] = 0.0;

   auto memory_info = Ort::MemoryInfo::CreateCpu(OrtArenaAllocator, OrtMemTypeDefault);
   Ort::Value input_tensor = Ort::Value::CreateTensor<float>(memory_info, input_tensor_values.data(), input_tensor_size, input_node_dims.data(), input_node_dims.size());
   auto t1 = std::chrono::high_resolution_clock::now();
   auto output_tensors = session.Run(Ort::RunOptions{nullptr}, input_node_names.data(), &input_tensor, 1, output_node_names.data(), 1);
   auto t2 = std::chrono::high_resolution_clock::now();

   float* floatarr = output_tensors.front().GetTensorMutableData<float>();
   for (int i = 0; i < 10; i++)
     printf("%f\t", i, floatarr[i]);

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>( t2 - t1 ).count();
  std::cout << std::endl << duration << std::endl;

}
