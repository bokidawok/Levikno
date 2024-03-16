#ifndef HG_LEVIKNO_VULKAN_BACKENDS_H
#define HG_LEVIKNO_VULKAN_BACKENDS_H

#include <vulkan/vulkan.h>
#include "vk_mem_alloc.h"

#include "levikno_internal.h"

namespace lvn
{
	struct VulkanQueueFamilyIndices
	{
		uint32_t graphicsIndex, presentIndex;
		bool has_graphics, has_present;
	};

	struct VulkanSwapChainSupportDetails
	{
		VkSurfaceCapabilitiesKHR capabilities;
		LvnVector<VkSurfaceFormatKHR> formats;
		LvnVector<VkPresentModeKHR> presentModes;
	};

	struct VulkanWindowSurfaceData
	{
		VkSurfaceKHR surface;
		VkRenderPass renderPass;
		VkSwapchainKHR swapChain;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		VkImage* swapChainImages;
		VkImageView* swapChainImageViews;
		VkImage depthImage;
		VmaAllocation depthImageMemory;
		VkImageView depthImageView;
		VkFramebuffer* frameBuffers;

		/* command buffers and semaphore/fence object count are dependent on the max frames in flight */
		VkCommandBuffer* commandBuffers;
		VkSemaphore* imageAvailableSemaphores;
		VkSemaphore* renderFinishedSemaphores;
		VkFence* inFlightFences;

		uint32_t swapChainImageCount;
		uint32_t swapChainImageViewCount;
		uint32_t frameBufferCount;
		uint32_t commandBufferCount;
		uint32_t imageIndex, currentFrame;

		bool frameBufferResized;
	};

	struct VulkanPipelineCreateData
	{
		LvnPipelineSpecification* pipelineSpecification;
		VkRenderPass renderPass;
		VkPipelineVertexInputStateCreateInfo vertexInputInfo;
		VkExtent2D* swapChainExtent;
		VkPipelineShaderStageCreateInfo* shaderStages;
		uint32_t shaderStageCount;
		VkDescriptorSetLayout* pDescrptorSetLayouts;
		uint32_t descriptorSetLayoutCount;
		VkPushConstantRange* pPushConstants;
		uint32_t pushConstantCount;
	};

	struct VulkanPipeline
	{
		VkPipeline pipeline;
		VkPipelineLayout pipelineLayout;
	};

	struct VulkanBackends
	{
		bool                                enableValidationLayers;
		VkInstance                          instance;
		VkDebugUtilsMessengerEXT            debugMessenger;
		LvnVector<VkPhysicalDevice>         physicalDevices;
		LvnVector<LvnPhysicalDevice>        lvnPhysicalDevices;
		
		VkPhysicalDevice                    physicalDevice;
		VkDevice                            device;
		VkQueue                             graphicsQueue;
		VkQueue                             presentQueue;
		VulkanQueueFamilyIndices            deviceIndices;
		VkPhysicalDeviceProperties          deviceProperties;
		VkPhysicalDeviceFeatures            deviceSupportedFeatures;

		VkCommandPool                       commandPool;
		VmaAllocator                        vmaAllocator;

		LvnPipelineSpecification            defaultPipelineSpecification;
		bool                                gammaCorrect;
		uint32_t                            maxFramesInFlight;
	};

	VulkanBackends* getVulkanBackends();
	void createVulkanWindowSurfaceData(LvnWindow* window);
	void destroyVulkanWindowSurfaceData(LvnWindow* window);
}

#endif
