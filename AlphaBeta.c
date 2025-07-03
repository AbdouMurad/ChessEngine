#include <stdlib.h>
#include "Board.h"
#include <stdio.h>
#include "AlphaBeta.h"

const long long unsigned int zobristTable[2][6][64] = {
    {
        {    
    0x44705db41c61fbdd,     0xf1f43c0f9d4ac921,     0xd8ea350244679cee,     0x4aea58f17f3fa831,
    0x1a5499fe88ab49bd,     0xa8d16df2b5db4b53,     0x102f6ad2cc6e8b64,     0xbf619f9f28d99e70,
    0xa5a03c9a9b7f284a,     0xb735d8f75b6f5c42,     0xba88a778621ae5ca,     0xd22ad34a806cbe12,
    0x1c8aa39192d3ef28,     0xee9a413c651c6489,     0x20bbfec535183e3b,     0xf2e7014cb5c26fec,
    0xc9f04d4212fe100e,     0xdf3fc48bb109b44d,     0x208c5937c9383b8a,     0xb4e982fdc5e9f8d4,
    0xd914aeb394db5762,     0x60ca2d00e46ae5df,     0xb36161e86f803a30,     0x8d1c57ede84e0f96,
    0x7693a2d052c6a44d,     0xee9abbbf46d36b25,     0x83d595914a46dfba,     0x29c7cfb2c3f2069a,
    0xd7c03dc06aad9e1d,     0xf938c3eb900c373c,     0xcb5b4c3060b2580e,     0xbf670bc0c71993f8,
    0x36430ce8408c24b2,     0x75ec7bb1c3fd8ea9,     0x8a500e3ce3ba973b,     0x00d462dfbe3b7e8a,
    0xab17c275a4f846b3,     0x034acf4ea99788f7,     0x065b047331328650,     0xadd86e6509b3f6d0,
    0x1f229ac613e412a3,     0x1cbc1c5ac93746b1,     0xacbf6622f2306e27,     0xa99c5285d28b3d92,
    0xbf8516307c937810,     0xf0bcf92a984931ca,     0x06c72fe9d48be4ba,     0xe0e1032767664478,
    0x80d1ddf82b1b1c56,     0x3f943a0643e6647d,     0x2cd8354bb9d96ccd,     0x465188b7a420ebba,
    0x178fca032331660c,     0x899d9d6799708055,     0xb375e0eda37aa379,     0x5c05f8f10609ae10,
    0xa83dd34041ba81f7,     0x0d063b5017b8ab82,     0x6f1a74fc33314480,     0xa66f0e5d1bfb8734,
    0x3565c659fc4a0be1,     0x35d99a5c2cd55bdb,     0x18aa160ee9510882,     0x1e3474f5866e6414},
        {    
    0x998c76bea4f51644,     0xaf48734d510a91ec,     0x0799cbd32a60c767,     0xf5c30f3fd99e9ff7,
    0x53c1edf1448d6330,     0xcabf2a880f04fdf9,     0xbd036e7b8e9f874a,     0x63b4ad24c910d649,
    0x971718afac16d90a,     0xecf67160ca5b5429,     0xe31f26dedab86c67,     0x517a0fff06dfdbb5,
    0x034d7e0d0ba07339,     0x835d9629f8354f5e,     0xb22c09a55af2359f,     0xb8027a8184bebe64,
    0xc875617ce66535da,     0x18584537bfe01772,     0x7845c9dc833bb444,     0x55385729be153c10,
    0x82a8b2b54894e5de,     0x91241baca5dc4d3b,     0xa44e0b867c50a988,     0xd42bc8d19e42fcac,
    0xfa80e26401f6ebd5,     0xf8c907b7a5b2c9d3,     0x856ca74c99ee1ac8,     0x06abd7193fbf3e87,
    0xbd7fed92b93d52fd,     0xe79950dea9e65191,     0xa218e5fc6c892e8e,     0xd98380087b5517fa,
    0x0200440c06ef8d55,     0x17e973a0241145da,     0x634dff5beef38826,     0x677822d0a9f76871,
    0x31e9539c8ce79f8e,     0xfebec0410947cd6f,     0xbc8dcb109a07168f,     0x9725fa2416364146,
    0x26e6710d114ee84b,     0x1c29154d275ae90b,     0x94d5aa6e9309d36a,     0x1ed6eb805e196741,
    0x530070cd23f1d480,     0x0bb75f603134bd5d,     0xd0367a784c30fb23,     0x8df4183d91926986,
    0x768ca137ea0c721d,     0xa8fea2c5491c786b,     0xfaffa22c3466142c,     0x741c40df8c29b846,
    0xaf62d6986c840d3b,     0x15481cf387a2b3a0,     0xf26fe8620f9b2797,     0xb54ff27aec02f0d0,
    0x735a832158f45c82,     0x2e6e491bc68d5106,     0x2127139120945dd4,     0x5025713edc0598d4,
    0x6ab06bfe24280cff,     0x4ce7e4c37ac4be23,     0x98b5ec2219746eb7,     0x4a9dc1283eb59b0a},
        {    0xcb9c97859210cf7a,     0x6f69a818f5476c75,     0x04b552c9ddb77050,     0x7d943521af2245f3,
    0xc57f6a15e3b1872a,     0x98aba9263b6a43be,     0x6de76dc4900b6056,     0x6b9374babbed609b,
    0xa9f4b48341b48dea,     0x4fe22be3df593430,     0x38517bfac1988390,     0xf08adb3323d363cf,
    0xebcbe5cff9004cf1,     0x2e4da8e2b799ffe9,     0xbc8b283f57b1b698,     0x2d75e054c9fa5737,
    0x0272b6512ff32cf5,     0xd53d2861803c8ac3,     0x4b3d78f5248402d8,     0x932c2b7293ae14ad,
    0xae82a92c45cd42ea,     0xfcb33ec3467320c1,     0xa62d688fe43eaa86,     0xb8ad767c678b9d86,
    0x39084b6d29e73217,     0x8261067f5f523649,     0x170930c7effec72e,     0xa68cbf1b874f489e,
    0xe69412468f5f42dc,     0x115e353c53067a0c,     0x1dc5f1ccbe5bb5ee,     0xb5b8634a5e331e44,
    0x12b0275664f6fb83,     0x72e0d77e3c83c818,     0xc9f93e2a6ed6d32c,     0xa89c2e5919da61d7,
    0xcff7f8046c7a6db9,     0xd30e2f6361bb5c66,     0x9966bf0e4bcb82c2,     0xa0dd7822c050e210,
    0x796d42138a5659a8,     0x742cfecce6a6b467,     0xe621ca81b1f5831d,     0x0687c2920630879d,
    0xd5722f8c4fbda5a1,     0x10b238ef39e074c6,     0xb8402f50724b29ae,     0x84f6ec0f9c678a87,
    0xb07f1bc2c1629e72,     0x9e20f1572a232298,     0x87e0cabb2e696e3d,     0x52cdae1ebbc94375,
    0x627469ae9623d04a,     0x59e26e90f8382ae3,     0x03fbef9d31062c00,     0x579a58793fc59149,
    0xfedd5b0fd9fb6421,     0x6485cd8fa7a0c91f,     0x8fcf3e4639e48300,     0x0726ad8cc71e5aa4,
    0xab0f9d35f226c6ec,     0x2f0bf872109cb4ed,     0xa34f33b5dd4338cb,     0x98c092dcf036e6fe},
        {   0x7116af10b6ba4731,     0x1deb5a0b0b6f6994,     0xab89acd7a0ce0a39,     0x7989f6ffa1b9f64f,
    0xed22480debc76f77,     0x6341f4ee27ecc76a,     0x36536aa637b9f2dc,     0xf2dc6d2de843a1ac,
    0xa0321dd0d383a9fb,     0x855e1a50b46f6002,     0xb15ef696aa1622ea,     0x1789014bf0c20303,
    0xfc0c8e9f8121256c,     0x2f82f1cedd6c0c1a,     0x49513cbc7687846c,     0x0e9edd2524fc7c66,
    0x0436ab5da4a1a6bb,     0x73cca94a8d73d6d3,     0x1175f7145df5d970,     0x1abf33aceda1e420,
    0x1d62d68d09711bb9,     0xa6d684517ed3c64b,     0x1b7001c75e065af9,     0x4ecb030905433f55,
    0xf72e394a4cffb039,     0x8945aff74d4efd46,     0x04aba1cb18a87415,     0xa3a4f85771d40487,
    0x0a286609e41aa5f2,     0x8aa3a51415601956,     0xddd16f26319783ba,     0x72e7661331123275,
    0xf6da322e34f75e20,     0x9fe291c258b70fb5,     0xb7607d9fe24fe4b8,     0xa1cedabcb0efc94a,
    0x4bf397089a3b90d5,     0xac9d9689b97ec3a2,     0x344f0acbb54b2de7,     0x772410a39230cdf4,
    0xd83022aa71a64e32,     0xc2b703dc82e7d565,     0xba989d39c98e2aa4,     0x41e9aba359c68908,
    0x75be0c69ff81394a,     0xef91adb87a008c43,     0xe73ff23f97f805a1,     0x83d78cb6a5f61322,
    0xf606022bd81ec263,     0x247da93e18728c1e,     0x360a8643e9417d09,     0xd0650e97e71ec885,
    0x142625078b36ab4a,     0x038d48568c759960,     0xf7696b6df82af9ab,     0x7500bf47c05e8f51,
    0xb2cb01ce71b16181,     0xff05939c570c2096,     0x75b825aefdcb47ce,     0xe3f6ca59d15fd23f,
    0x8fe69cbde53ae0c3,     0xaab0c9c69da14c20,     0x28ffeb82c0905acd,     0xd588cc40c2777517},
        {0x1986a6bb2c375243,     0xadeef8a3c33d34f5,     0xc1b59076c38ff90a,     0x067b1efecbbb62af,
    0x8b11fed8a705b44c,     0x2b557d84db27e5a2,     0xfabec949f0dbac56,     0xf95ea3bf93a71cec,
    0x7676938cd65fe600,     0xc0ebce4422b79afa,     0xdda0d531c67f7d6a,     0xe821f2e96c753dba,
    0x1eb0abfde3027737,     0x512a618f6425e925,     0x00ce7d5b5e808875,     0x024ea188472b6247,
    0xae851e9d7c759ac0,     0x7144d99d55a7ae49,     0x7c76c9a2fc6c0e17,     0x417f941cbbfee374,
    0xc60b1ce0c45692d4,     0x3db0cf47240921fa,     0x7ea1332f2edcc033,     0x7586fcbaaed9e95c,
    0x8b0e54f9132177b2,     0xd7b8ac135a15a18b,     0xbdb78870485acef1,     0x74b08b0f5a8622c6,
    0xf1ae4a72bbe1a03d,     0x8ea96bba0ad4a0a4,     0xe30518425d5e5071,     0x861b1d163c4e4866,
    0xa5cfc3e51dca1ee0,     0xfba29dad0532a6a1,     0xa9d9c62de2c4fdb1,     0x749689a8f4fc63f6,
    0x5976fe683ddba53f,     0xf7149f830fed055a,     0xca1da91c27e157ba,     0xed55e64b4a936b6d,
    0x7956db18850c4c1c,     0x846058337bc918c4,     0x082d72ef2a1759ac,     0x0d44756151ecc8c6,
    0xd2dd043c8cb74678,     0x5daddbcd1b36de59,     0xc89622710b5dabbd,     0x2502da5dc8e6da25,
    0x7bf80406bbfbd856,     0x2cfb0c188709fc13,     0x7ea46120256feb02,     0x04811c749e771dbd,
    0xc2efec2fbae725b7,     0xd3e93af10e609ab3,     0x0cb11b6fdf06738d,     0x2e9a1bb671fe48e3,
    0x1f9f02eb7cdea318,     0x197f007f29f59217,     0x41ba2e4185548c5c,     0x3d2322651076ffb6,
    0x62aebdca3f913719,     0x4876a38f7b80c82a,     0x2bfe3f540b32c535,     0x3b9f1520624b0b5f},
        {    0x58fdc26a1b628b00,     0x1f88729e6f707343,     0xa6e86638a52cb376,     0x188c9da902ce63a3,
    0xba4cbebc41fcbdaf,     0x0877aa4f2314240b,     0x3797d0540ae730d9,     0x28429439bd02411e,
    0xddb4e4af55df6073,     0xd758e33290ed9c22,     0x2166be52147d6c14,     0xaac721edf07a379b,
    0x9a72414cf676ec87,     0xdf711a89119a5788,     0x36799f5b368e83b8,     0x9e69cd3bb8da6e16,
    0x4fcd94ca7fa01049,     0x4ca99b2bfe81f40f,     0x9718eba4b8867742,     0xbad3c80d4c46c243,
    0xe6236def09865a3e,     0x7cb281e60cde1323,     0xd1970507832af684,     0x0e211d352dba008c,
    0x65a93ab9ac7d2532,     0x8b6ba7629bb22863,     0x296316066db5e4d6,     0xa1c94633d0bd0eab,
    0x6c4ea4eaa7954222,     0x1b289527ca545ecb,     0x0bcb9226e0ad27d6,     0x78d9f48d5939c65b,
    0xf957563d30d21d8a,     0x6476ccec6596c5dc,     0xac2ebcd813dafc9a,     0x2b95b32672d1b864,
    0x400e1ead23799efe,     0xb868fe186185f464,     0x4f7ccf3284cb8210,     0xc1848dc1353568fe,
    0xba048a857f9513fd,     0x80b625141fa2e7de,     0xbfcf82364e2fc9c0,     0xed79c482d3c0e9b5,
    0x40d78519d6f5928d,     0x554cc0cdb58d950e,     0xa3f3f0fd926a71c6,     0x53c9729760bc70bd,
    0xf317e230c9825eba,     0x97231ce91f9dc68d,     0xe5108d1b2e42051e,     0x43d90aef9d2016f3,
    0x45b8d0d8bf3d2a54,     0x13d0359211684d66,     0x107e613ac5cdec7d,     0xab288c1fd2532679,
    0xb064ea023c4dc5db,     0x3f38e766bc8d9b44,     0xb2ee8e2466955fee,     0x41e2140deddb6def,
    0x8a5ea265e1fd93af,     0xb0c4a8f00bad6fd9,     0xa31b5ee50b62b79d,     0xe8fd286412f87bdf,}
    },
    {
        {    0xc764298210186a12,     0x278c6453852d4577,     0x563a432f58948855,     0x19805bc4be5bafca,
    0x083fd6a414208c11,     0x93fffe6f8084429d,     0x0bac157673546aa0,     0xbb2b86e66709f3e9,
    0x81cc0b153393f193,     0x79f3528a59a2be63,     0x7032678837a2143d,     0x8a4cd9499bfa72b9,
    0xf4e6ff3101011edb,     0x8cd4d3bef296397d,     0xa342aa5f14b3b276,     0x5cb898953cfd384b,
    0x234a3238114e7bb2,     0x5dd31c7f575cf4c5,     0x786d7942f204b0dc,     0x72344b547c235bd4,
    0xab32e4b85768dcee,     0xce39bf5843dba9ae,     0xfb83005f8c932465,     0xd7d24108de7d56ed,
    0x56f4ff9bf4ab70be,     0x9fa1f7fa5f62b022,     0x953c563636f05b35,     0xa6a3a91a8b9f07cb,
    0xb4b05b8e912d5795,     0x4b7dee0d51d86431,     0x9cd5cd04ed600043,     0x4e4cc8f505bbae37,
    0xb0497469bbddfab0,     0x67e8a9cf5dd0a9c3,     0xac745f6f707b60c2,     0xfea82ecdd1a8bd5f,
    0xabc90c5a74b2a5aa,     0x069c577ed8761186,     0x2d43cc0a327bca70,     0xaf6f6e58a7196a6d,
    0x76fca07ca9e04971,     0xaeed23070facbe4f,     0x7d5dced2e42ef68e,     0x375aaf5288577ed9,
    0x5c0fb58cb5b13de3,     0x405753d914ad6c96,     0xa607eea3399a8872,     0xf637d2eb8be4c1f6,
    0x083ca8d03f942875,     0xa41cd2677b000447,     0xcdea0c06b1d801cf,     0x8d15e6c2b440527e,
    0xb4f03ae567e43a52,     0xe4bb4d424c3b0ff9,     0xe90fd51e237d5c37,     0x67a023f74960120d,
    0x18af5cae7339cb4e,     0x351e63d4bfae18a3,     0x5fbab42ac850e46d,     0x96fee2d79306234e,
    0x805c5420aa0b61ac,     0x62ee7e8bfaa6663a,     0x0476edc388a326af,     0x9e8873f342f84a0d},
        {    0xff0f8790d34301a3,     0x15a6fbfa1bd901d3,     0x7d31d8f7268c4ded,     0xca3a5ef5b6df6737,
    0xfc74f3c17cc586c4,     0x4673c5791ec14cf1,     0x4bab401ae36c5f3b,     0x29432fdabdb5f12a,
    0xfebf502b29b8a463,     0x79869cb9f96332bb,     0x57a412c521fe4778,     0x83f0e7824f4408bc,
    0x0611d6ee152cac1a,     0x21026a03a4799e68,     0xf1388b224c494d69,     0xe59da32dd9313c4a,
    0x27a2593adc9939ec,     0x91bb5ff8051fb406,     0x3b2dc2dda45d6ff4,     0x7ebd3786d9bb518a,
    0xa47e7ea0d7993a4d,     0x60f25f2095e2fcce,     0x362e156aee661660,     0xae75d46049303915,
    0x1ec0cd9f4dcf77aa,     0x5f607bcc7b286240,     0xd5687bb583f717d3,     0x1c743a8cdeb52d2b,
    0xf08d4362a5a23d11,     0x5d2ba12bb644b79d,     0xed0b3e64ce0c4a8d,     0x8251f05fc627695d,
    0x6e344478565773b0,     0x2752eabe8e8e65e5,     0xa0265b62c1b0a214,     0x8dfde7565f1376f5,
    0xe520cd65b888765c,     0x4502160ce6fdf84e,     0x4e1b3cbcdf0f739c,     0xfb96bc7e355d1628,
    0x36535a3810737ade,     0x6d9ffff52965d223,     0x1e1a44e2e8612c2b,     0x31db15155d5d2be9,
    0xcee676166890ece2,     0x86717f65072ed483,     0xa9c6715690defefd,     0x285223be056933dd,
    0x017d1285c259d8e9,     0x4b43937124610ddd,     0xd6601cd5e424e2c8,     0xb124f64b20ac02f9,
    0x58da2bc6c8f717ae,     0x5c6f5d0f9c1e3a32,     0xccd6f579a353284c,     0x1e61942bde8e8e45,
    0x7beae5ffec0dd53d,     0x07ab385166cfb62e,     0xda5459ceecaa2b5f,     0x31a0defe77b7755c,
    0xdc12004bcabdd480,     0xd9344e86739b1ca3,     0x1eb777e2bd84c739,     0x998c3b7447dead31},
        {    0xf9db1e87f8790636,     0xcb9670f3d85b10a7,     0xaa7c6d9de77f7e15,     0x949562ea473f90d0,
    0x9810da7102e18f66,     0x6d379a964391e6e3,     0xb7a1da5cf7378984,     0x971a74c749b4d17a,
    0xd982395cc1a99ab4,     0x21ed56e07cafa802,     0x291fc750386e6dd9,     0xdb63b5e385b1de76,
    0x0a21969b1d8f9cf9,     0xbd2ff3602dc47178,     0x727d07d3ce54227a,     0x4e616dc9936389de,
    0x112c2c1130eae40b,     0xd45320c5d22a95f6,     0x91d37f73669489ee,     0x9fe1285ecee81319,
    0xc95bb4e4e7107f37,     0x2929f5aa74f377cc,     0x8f61371b8c77bd1c,     0x0c8d0903dc922161,
    0x3efca4d84c0762de,     0xa5ba59fbc1e5f72e,     0x30773f41270dade3,     0x9050d1351044b143,
    0x23777faf34316373,     0x57265d155a470342,     0x171c918f6e9c4ec4,     0x271a4776ea10f234,
    0xfa1a526724f13884,     0xfd27d0334e67cc4e,     0xd6c2c9822a35bc5d,     0x63f74bd8a6e65b75,
    0x5300320fd2fc42c0,     0x3d45091533f81757,     0xf188dd33a9e9a45b,     0x9cc310ea8f356409,
    0x90b361f82ff693f5,     0xe8953a492caec964,     0xb9d1311dc6bfabc3,     0x839f26d46cc81c2f,
    0xbc941d9d5d60a51b,     0xf28e5c1d2b90b1df,     0x2e6a5d2ad10a33a7,     0x6ad72ccd2a88c918,
    0x34f4ed2d2f942c85,     0x4b9663816235afb2,     0xc9590b0e94e9b109,     0x8e1d9f06f9d490b4,
    0x728a66cf4c61da01,     0xa4204880681a5f48,     0x8f1aaac26c09bf09,     0x743b5280e9520fe9,
    0xde6767436f2bf89e,     0x9b7ae12ec1380828,     0x3ea14e626e8655a1,     0x7be00b3081317524,
    0xe4a8667b7c8c2648,     0x4d76bf75b7562543,     0x633912faa61829d6,     0x2a242db08ca8a2d4},
        {    0xff081c66e22a39e7,     0xe5198cb6051f79b2,     0xc2dbca2de0c1f8c7,     0x42b4f93c502646e6,
    0x37909b167343b2ae,     0xfb41fe98f2997f2d,     0x1fce26c3878b10e9,     0x00c66f2f1929751b,
    0x35d666f5cb69fda5,     0x3567e54faed6c7ae,     0x95057fce4cb16ad5,     0xbec3cc77642f87fe,
    0xda8f8459ad307edb,     0x3a50cb66ab5b8adb,     0x78605de1e8210783,     0x34c89101813cb203,
    0x054cc38030583ead,     0xa9a13bfe2b1d1efb,     0x5883a6dc64c52543,     0x5543510a63e54d0b,
    0xc54d252a38e2b756,     0xcd61d47ce1208920,     0x175f9adc09c266dc,     0xc883cb7fddb18a68,
    0x804d31dafaa41411,     0xbeb6a6a69c615028,     0xce21d4d65c465719,     0xdaa110b6c5559ec1,
    0xa11c4aa0c491fe53,     0x343a44694f304a0c,     0xfa42d235a6393065,     0xa71fb062d1acc19d,
    0x54577c407dcc57b2,     0x1d45fbb3fcb7979b,     0x198061bb78dd58d6,     0xef65f2bb3c6a6cea,
    0xa9b869f6c9f156fd,     0x7c3bb6a89bb1333d,     0xf3d250cf711c3c9d,     0x652eca87c5d4a2e6,
    0x4c83c527c7831399,     0x3e1624d746429d79,     0x717626d0b51d3c0f,     0x0412d576927b13c6,
    0x3a629735133b7596,     0xfdafea62b4918d3e,     0x99c1297b9510aeea,     0xa68f63658cfd57fc,
    0x0e466be273f9af37,     0xbd7ef4fa3e244cc7,     0x6dba08ca57dd03d1,     0x540706bc3b9cb327,
    0xcb203d7b800498ba,     0xeaec8ad91d7a7cd8,     0x6582e28899985d4f,     0xea8f694f72849410,
    0x6473eb84d0fa1ce0,     0x5608df022dc33dcf,     0xaac33d5807039cf4,     0x061995e518f175e2,
    0x0540d9ad6640b550,     0xb7ebe2190db640ff,     0x1f0d8a2c49ebf1b8,     0xf3b503c907236ffe},
        {    0x7ab49eae8d78f43a,     0xab01c3fdfbcc12d0,     0x8dbcc6915b674546,     0xc7c458fe3ebfcad0,
    0x535bb14b2a4e167c,     0x7da13a56bdd11671,     0x5691820d60f993e7,     0x3e1a0b5eff0f3d33,
    0x3f1e60dcdabb8db1,     0xa88e0f8d6de3f518,     0xf0a5121ed29d3538,     0x3e01b24fdfd06d34,
    0xfb3953dfe5384ca8,     0x285d1ecfb4dba7f2,     0xf56055faaa7c9ddc,     0x972e0bb7388611aa,
    0x49bd091151ac450a,     0x07ea56168133c020,     0xbe024c157264ebd7,     0xa31baf7cd05e8944,
    0x009351478163dfd6,     0x251278cc556a56c9,     0x37de0e5d9c70fcb9,     0x9675cee31b7ff906,
    0x44ffe1ae0ab94fcb,     0xe0a0c5166bf3ced7,     0x17da21d1fd6065a5,     0x7bbc92dab58a7466,
    0x4421c1574c2522b7,     0x1972f847214cb3a8,     0xdc76723f04394480,     0x535144746e564dfb,
    0xbdac914aba412b22,     0x5569efdff487b0cc,     0x5e616a0c099865d4,     0x7c28c1e8b1b202af,
    0x602153bfa3044746,     0x945e46e996fe9671,     0x502a418d9a4e45f7,     0x4e2eb56d49cdf989,
    0x1aec8b334299bed1,     0x826630431230bfd2,     0xb4cc41485305febd,     0x417c9852921f9f72,
    0x2f92371200a799f1,     0x3f1999aab8d6af87,     0xa94167b9411e14c4,     0x1dab07178ce7c93b,
    0x2f08bc86f96f73a2,     0x33bf4b2ef9b24501,     0x9ad924069025866b,     0x0abeb6f9197d8cd5,
    0xd53948f1c820b46a,     0x044b848e294964aa,     0x6278c9ac4642c1fa,     0x2c07dd49d56b48ff,
    0x45a2dd275bbdda7b,     0xd7927cea39263b8f,     0x96c9c9cedc737f8c,     0x649740101c84a8e5,
    0x12df5355d7ca8de8,     0x539747085b2de90d,     0x04b57cf52d7cf72b,     0xc20f8e7355f9d8d3},
        {    0x2517efcccccd3cf9,     0x68b1a4742b41d851,     0x6a29155556fe8bae,     0x4ebc7119e15ef5e5,
    0x5a85e0f65cd71384,     0x13573296b3eec56d,     0x34c4afaaebbabb59,     0x77df1eebebec038b,
    0xe1f46439be974012,     0x48914bf2ac27e25a,     0x934a11c55c77c138,     0x14cd6ca1ef98cd41,
    0xd61612bd3c904709,     0x10d7edeb64eacccf,     0x79c57ec13ca52a18,     0x7dcbc553087e4c06,
    0x5fc9cd79df43a7e6,     0xcb13844838bb7b02,     0xd5f1465cd452ccf4,     0x2cb154ebe457fc67,
    0x94cf4f20352fac08,     0x3d80c7e56602cf42,     0xbdda994b556b5ad3,     0xa593d25d756e80ce,
    0xe07bf91659273fc6,     0xd78e49bd0eefa52d,     0x89a1875b63723d2b,     0x949f49ac958caa0b,
    0x6e33ae9029aa8bb3,     0x13cfaf5c4d68f804,     0x426d5994b9a0d5a1,     0xace0f152e77fdb9e,
    0x35304e5dc6fd3095,     0x59e2567a0c5135c5,     0x5b331fad3b661a61,     0x9e64b8382c4aa0f5,
    0x2062990f1974c57e,     0x1c6cf9aa0c8dc078,     0x30e167f92fd3af56,     0x07f1d8545d93dc7c,
    0xa6f878c50e446d9f,     0x66386bcc7424be1c,     0x53b84466f2018ca6,     0x640e086b75db74f5,
    0x19943349e708a4cf,     0x29de34c3a7d51ea0,     0xb3135a3cc0686a09,     0xaee096f3886cd537,
    0xb87c0b8de976cef9,     0x627c98871b5bdf32,     0xc6a65f8d196773f1,     0x04266bc8b2592b56,
    0xfd8d07dcc4d7c310,     0xfefea0d387b8a2b0,     0x0dd31be83c383c35,     0xfb8c5343d676db82,
    0x06f2e99e2be875ba,     0x13ac8c53c6889bba,     0x9eb199c5a4d2e932,     0x02f8909b1b5d2984,
    0xc7256ba02b0fa2d3,     0xa1a6167fbb36b579,     0xf46a693d28d72715,     0xf49bfc231504e3dc,}
    }
};
const long long unsigned int blackHash = 14721544785632194438ULL;
const long long unsigned int castleHash[4] = {
    0xA3B1C2D3E4F50617ULL,  // White kingside
    0x8F92A1B0C3D4E5F6ULL,  // White queenside
    0x123456789ABCDEF0ULL,  // Black kingside
    0xFEDCBA9876543210ULL   // Black queenside
};


int pieceValue[] = {1000000,100,300,300,500,800};

int pawnPstMg[64] = {
     0,   0,   0,   0,   0,   0,   0,   0,
   10,  10,   0,  -5,  -5,   0,  10,  10,
    5,   0,   0,   5,   5,   0,   0,   5,
    0,   0,  10,  20,  20,  10,   0,   0,
    5,   5,  10,  25,  25,  10,   5,   5,
   10,  10,  20,  30,  30,  20,  10,  10,
   50,  50,  50,  50,  50,  50,  50,  50,
     0,   0,   0,   0,   0,   0,   0,   0
};
int pawnPstEg[64] = {
     0,   0,   0,   0,   0,   0,   0,   0,
   20,  20,  20,  25,  25,  20,  20,  20,
   15,  15,  15,  20,  20,  15,  15,  15,
   10,  10,  10,  15,  15,  10,  10,  10,
    5,   5,   5,  10,  10,   5,   5,   5,
    0,   0,   0,   5,   5,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,
     0,   0,   0,   0,   0,   0,   0,   0
};

int knightPstMg[64] = {
   -50, -40, -30, -30, -30, -30, -40, -50,
   -40, -20,   0,   5,   5,   0, -20, -40,
   -30,   5,  10,  15,  15,  10,   5, -30,
   -30,   0,  15,  20,  20,  15,   0, -30,
   -30,   5,  15,  20,  20,  15,   5, -30,
   -30,   0,  10,  15,  15,  10,   0, -30,
   -40, -20,   0,   0,   0,   0, -20, -40,
   -50, -40, -30, -30, -30, -30, -40, -50
};
int knightPstEg[64] = {
   -40, -30, -20, -20, -20, -20, -30, -40,
   -30, -10,   5,   5,   5,   5, -10, -30,
   -20,   5,  10,  15,  15,  10,   5, -20,
   -20,   5,  15,  20,  20,  15,   5, -20,
   -20,   5,  15,  20,  20,  15,   5, -20,
   -20,   5,  10,  15,  15,  10,   5, -20,
   -30, -10,   0,   0,   0,   0, -10, -30,
   -40, -30, -20, -20, -20, -20, -30, -40
};

int bishopPstMg[64] = {
   -20, -10, -10, -10, -10, -10, -10, -20,
   -10,   5,   0,   0,   0,   0,   5, -10,
   -10,  10,  10,  10,  10,  10,  10, -10,
   -10,   0,  10,  15,  15,  10,   0, -10,
   -10,   5,  10,  15,  15,  10,   5, -10,
   -10,   0,  10,  10,  10,  10,   0, -10,
   -10,   0,   0,   0,   0,   0,   0, -10,
   -20, -10, -10, -10, -10, -10, -10, -20
};
int bishopPstEg[64] = {
   -10, -5, -5, -5, -5, -5, -5, -10,
    -5, 10, 10, 10, 10, 10, 10,  -5,
    -5, 10, 15, 15, 15, 15, 10,  -5,
    -5, 10, 15, 20, 20, 15, 10,  -5,
    -5, 10, 15, 20, 20, 15, 10,  -5,
    -5, 10, 15, 15, 15, 15, 10,  -5,
    -5, 10, 10, 10, 10, 10, 10,  -5,
   -10, -5, -5, -5, -5, -5, -5, -10
};

int rookPstMg[64] = {
     0,   0,   5,  10,  10,   5,   0,   0,
    -5,   0,   0,   5,   5,   0,   0,  -5,
    -5,   0,   0,   0,   0,   0,   0,  -5,
    -5,   0,   0,   0,   0,   0,   0,  -5,
    -5,   0,   0,   0,   0,   0,   0,  -5,
    -5,   0,   0,   0,   0,   0,   0,  -5,
     5,  10,  10,  10,  10,  10,  10,   5,
     0,   0,   0,   5,   5,   0,   0,   0
};
int rookPstEg[64] = {
     0,   5,   5,  10,  10,   5,   5,   0,
     0,   0,   0,   5,   5,   0,   0,   0,
    -5,   0,   0,   5,   5,   0,   0,  -5,
    -5,   0,   0,   5,   5,   0,   0,  -5,
    -5,   0,   0,   5,   5,   0,   0,  -5,
    -5,   0,   0,   5,   5,   0,   0,  -5,
     5,  10,  10,  20,  20,  10,  10,   5,
     0,   0,   5,  10,  10,   5,   0,   0
};

int queenPstMg[64] = {
   -20, -10, -10,  -5,  -5, -10, -10, -20,
   -10,   0,   0,   0,   0,   0,   0, -10,
   -10,   0,   5,   5,   5,   5,   0, -10,
    -5,   0,   5,   5,   5,   5,   0,  -5,
     0,   0,   5,   5,   5,   5,   0,  -5,
   -10,   5,   5,   5,   5,   5,   0, -10,
   -10,   0,   5,   0,   0,   0,   0, -10,
   -20, -10, -10,  -5,  -5, -10, -10, -20
};
int queenPstEg[64] = {
   -10,  -5,  -5,  -5,  -5,  -5,  -5, -10,
    -5,   0,   0,   0,   0,   0,   0,  -5,
    -5,   0,   5,   5,   5,   5,   0,  -5,
    -5,   0,   5,  10,  10,   5,   0,  -5,
    -5,   0,   5,  10,  10,   5,   0,  -5,
    -5,   0,   5,   5,   5,   5,   0,  -5,
    -5,   0,   0,   0,   0,   0,   0,  -5,
   -10,  -5,  -5,  -5,  -5,  -5,  -5, -10
};

int kingPstMg[64] = {
   -30, -40, -40, -50, -50, -40, -40, -30,
   -30, -40, -40, -50, -50, -40, -40, -30,
   -30, -40, -40, -50, -50, -40, -40, -30,
   -30, -40, -40, -50, -50, -40, -40, -30,
   -20, -30, -30, -40, -40, -30, -30, -20,
   -10, -20, -20, -20, -20, -20, -20, -10,
    20,  20,   0,   0,   0,   0,  20,  20,
    20,  30,  10,   0,   0,  10,  30,  20
};
int kingPstEg[64] = {
   -50, -30, -30, -30, -30, -30, -30, -50,
   -30, -10,   0,   0,   0,   0, -10, -30,
   -30,   0,  10,  15,  15,  10,   0, -30,
   -30,   0,  15,  20,  20,  15,   0, -30,
   -30,   0,  15,  20,  20,  15,   0, -30,
   -30,   0,  10,  15,  15,  10,   0, -30,
   -30, -10,   0,   0,   0,   0, -10, -30,
   -50, -30, -30, -30, -30, -30, -30, -50
};

int *mgPst[6] = {
    kingPstMg, pawnPstMg, knightPstMg, bishopPstMg, rookPstMg, queenPstMg
};
int *egPst[6] = {
    kingPstEg, pawnPstEg, knightPstEg, bishopPstEg, rookPstEg, queenPstEg 
};

//old psts
/*
{
int eg_pawn_table[64] = {
      0,   0,   0,   0,   0,   0,   0,   0,
    178, 173, 158, 134, 147, 132, 165, 187,
     94, 100,  85,  67,  56,  53,  82,  84,
     32,  24,  13,   5,  -2,   4,  17,  17,
     13,   9,  -3,  -7,  -7,  -8,   3,  -1,
      4,   7,  -6,   1,   0,  -5,  -1,  -8,
     13,   8,   8,  10,  13,   0,   2,  -7,
      0,   0,   0,   0,   0,   0,   0,   0,
};
int eg_knight_table[64] = {
    -58, -38, -13, -28, -31, -27, -63, -99,
    -25,  -8, -25,  -2,  -9, -25, -24, -52,
    -24, -20,  10,   9,  -1,  -9, -19, -41,
    -17,   3,  22,  22,  22,  11,   8, -18,
    -18,  -6,  16,  25,  16,  17,   4, -18,
    -23,  -3,  -1,  15,  10,  -3, -20, -22,
    -42, -20, -10,  -5,  -2, -20, -23, -44,
    -29, -51, -23, -15, -22, -18, -50, -64,
};
int eg_bishop_table[64] = {
    -14, -21, -11,  -8, -7,  -9, -17, -24,
     -8,  -4,   7, -12, -3, -13,  -4, -14,
      2,  -8,   0,  -1, -2,   6,   0,   4,
     -3,   9,  12,   9, 14,  10,   3,   2,
     -6,   3,  13,  19,  7,  10,  -3,  -9,
    -12,  -3,   8,  10, 13,   3,  -7, -15,
    -14, -18,  -7,  -1,  4,  -9, -15, -27,
    -23,  -9, -23,  -5, -9, -16,  -5, -17,
};
int eg_rook_table[64] = {
    13, 10, 18, 15, 12,  12,   8,   5,
    11, 13, 13, 11, -3,   3,   8,   3,
     7,  7,  7,  5,  4,  -3,  -5,  -3,
     4,  3, 13,  1,  2,   1,  -1,   2,
     3,  5,  8,  4, -5,  -6,  -8, -11,
    -4,  0, -5, -1, -7, -12,  -8, -16,
    -6, -6,  0,  2, -9,  -9, -11,  -3,
    -9,  2,  3, -1, -5, -13,   4, -20,
};
int eg_queen_table[64] = {
     -9,  22,  22,  27,  27,  19,  10,  20,
    -17,  20,  32,  41,  58,  25,  30,   0,
    -20,   6,   9,  49,  47,  35,  19,   9,
      3,  22,  24,  45,  57,  40,  57,  36,
    -18,  28,  19,  47,  31,  34,  39,  23,
    -16, -27,  15,   6,   9,  17,  10,   5,
    -22, -23, -30, -16, -16, -23, -36, -32,
    -33, -28, -22, -43,  -5, -32, -20, -41,
};
int eg_king_table[64] = {
    -74, -35, -18, -18, -11,  15,   4, -17,
    -12,  17,  14,  17,  17,  38,  23,  11,
     10,  17,  23,  15,  20,  45,  44,  13,
     -8,  22,  24,  27,  26,  33,  26,   3,
    -18,  -4,  21,  24,  27,  23,   9, -11,
    -19,  -3,  11,  21,  23,  16,   7,  -9,
    -27, -11,   4,  13,  14,   4,  -5, -17,
    -53, -34, -21, -11, -28, -14, -24, -43
};
int pawnPst[] = {
    0,  0,  0,  0,  0,  0,  0,  0,
    5, 10, 10,-20,-20, 10, 10,  5,
    5, -5,-10,  0,  0,-10, -5,  5,
    0,  0,  0, 20, 20,  0,  0,  0,
    5,  5, 10, 25, 25, 10,  5,  5,
    10, 10, 20, 30, 30, 20, 10, 10,
    50, 50, 50, 50, 50, 50, 50, 50,
    0,  0,  0,  0,  0,  0,  0,  0};
int knightPst[] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50};
int bishopPst[] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20};
int rookPst[] = {
     0,  0,  5,  10, 10, 5,  0,  0,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
    -5,  0,  0,  0,  0,  0,  0, -5,
     0,  10, 10, 10, 10, 10, 10, 0,
     0,  0,  0,  0,  0,  0,  0,  0,};
int queenPst[] = {
    -20,-10,-10, -5, -5,-10,-10,-20
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
     -5,  0,  5,  5,  5,  5,  0, -5,
     -5,  0,  5,  5,  5,  5,  0, -5,
    -10,  0,  5,  5,  5,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20,};
int kingPst[] = {
     20,  30,  10,  0,   0,   10,  30,  20,
     20,  20,  0,   0,   0,   0,   20,  20,
    -10, -20, -20, -20, -20, -20, -20, -10,
    -20, -30, -30, -40, -40, -30, -30, -20,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
    -30, -40, -40, -50, -50, -40, -40, -30,
};
}*/

int max(int a, int b) {
    return a > b ? a : b;
}
int min(int a, int b) {
    return a < b ? a : b;
}
int abs(int a) {
    return a > 0 ? a : -1 * a;
}

struct TTEntry *probe(long long unsigned int key, struct TTEntry *table) {
    int hash = key % TT_SIZE;
    struct TTEntry *entry = &table[hash];
    if (entry->key == key) return entry;
    return NULL;
}

//store in ttTable
void store(long long unsigned int key, int depth, int score, int flag, struct Move BestMove, struct TTEntry *table) {
    int index = key % TT_SIZE;
    struct TTEntry *entry = &table[index];
    if (entry->depth < depth || entry->key == 0) {
        entry->depth = depth;
        entry->score = score;
        entry->flag = flag;
        entry->key = key;
        entry->BestMove = BestMove;
    }
}

long long unsigned int computeHash(struct gameBoard *Game, enum Color Turn) {
    long long unsigned int result = 0b0;
    long long unsigned int current;
    int pos = 0;
    if (Turn) result = blackHash;
    for (int col = 0; col <= 1; ++col) {
        for (int piece = 0; piece <= 5; ++piece) {
            current = Game->game[col][piece];
            while (current) {
                pos = __builtin_ctzl(current);
                result ^= zobristTable[col][piece][pos];
                current &= current - 1;
            }
        }
    }
    if (Game->BlackCastle == BlackBoth) {
        result ^= castleHash[2];
        result ^= castleHash[3];
    }
    else if (Game->BlackCastle == BlackKing) result ^= castleHash[2];
    else if (Game->BlackCastle == BlackQueen) result ^= castleHash[3];
    
    if (Game->WhiteCastle == WhiteBoth) {
        result ^= castleHash[0];
        result ^= castleHash[1];
    }
    else if (Game->WhiteCastle == WhiteKing) result ^= castleHash[0];
    else if (Game->WhiteCastle == WhiteQueen) result ^= castleHash[1];
    
    return result;
}

void InsertSort(struct Move *moves, int count) {
    if (count < 2) return;
    if (count < 3) {
        if (moves[0].score < moves[1].score){
            struct Move move = moves[0];
            moves[0] = moves[1];
            moves[1] = move;
        }
        return;
    }
    struct Move temp;
    int j = 0;
    for (int i = 1; i < count; ++i) {
        temp = moves[i];
        for (j = i - 1; j >= 0 && moves[j].score < temp.score; --j) {
            moves[j+1] = moves[j];
        }
        moves[j+1] = temp;
    }
}

void printMoves(struct MoveList *moves) {
    printf("Moves: %d \n", moves->count);
    for (int i = 0; i < moves->count; ++i) {
        if (i % 3 == 0) printf("\n");
        printf("[%d : %d - %d - %d", moves->moves[i].start, moves->moves[i].end, moves->moves[i].piece, moves->moves[i].score);
        if (moves->moves[i].piece == Pawn && (moves->moves[i].end/8 == 7 | moves->moves[i].end/8 == 0)) printf(" - %d] ", moves->moves[i].promotion);
        else printf("] ");
    }
    printf("\n");
}

void setupStack(struct Stack *stack) {
    stack->size = 32;
    stack->stack = malloc(sizeof(unsigned long long int) * stack->size);
    stack->pointer = 0;
}

void deleteStack(struct Stack *stack) {
    free(stack->stack);
    stack->pointer = 0;
    stack->size = 0;
}

void push(struct Stack *stack, unsigned long long int value) {
    stack->stack[stack->pointer++] = value;
    if (stack->size == stack->pointer) {
        stack->size *= 2;
        unsigned long long int *newStack = malloc(sizeof(unsigned long long int) * stack->size);
        for (int i = 0; i < stack->pointer; ++i) {
            newStack[i] = stack->stack[i];
        }
        free(stack->stack);
        stack->stack = newStack;
    }
}
long long unsigned int pop(struct Stack *stack) {
    if (stack->pointer < 0) return 0;
    
    return stack->stack[stack->pointer--];
}

int search(struct Stack *stack, unsigned long long int value) {
    int count = 0;
    for (int i = 0; i < stack->pointer && count < 3; ++i) if (stack->stack[i] == value) count += 1;
    return count;
}

void generateMoves(struct gameBoard *Game, struct MoveList *moves, enum Color color) {
    //generate all possible moves for color side
    moves->count = 0;
    int position = 0;
    long long int currentPiece = 0;
    struct gameBoard newGame = *Game;
    for (int Piece = Queen; Piece >= King; --Piece){
        enum Piece piece = (enum Piece)Piece;
        if (piece == Pawn) {
            currentPiece = Game->game[color][piece];
            while (currentPiece){
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                //en passant
                if (Game->enPassant[!color] < 8 && position/8 == 4 - color) {
                    if (abs(Game->enPassant[!color] - position%8) == 1) {
                        newGame.game[color][Pawn] ^= 1ULL << position;
                        newGame.game[color][Pawn] |= 1ULL << (position/8 + 1 - 2 * color)*8 + Game->enPassant[!color];
                        newGame.game[!color][Pawn] ^= 1ULL << (position/8 + 1 - 2 * color)*8 + Game->enPassant[!color] - 8 + 16 * color;
                        if (!inCheck(&newGame, color)) {
                            struct Move move = {position, (position/8 + 1 - 2 * color)*8 + Game->enPassant[!color], piece};
                            move.score = 1000;
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            moves->moves[moves->count++] = move;
                        }
                        newGame = *Game;
                    }
                }
                if (position/8 == 1 +5*color && !(((1ULL << (position + 8 - 16 * color)) | (1ULL << (position + 16 - 32 * color))) & AllBitBoard(Game))) { //pawn move 2 forward
                    newGame.game[color][Pawn] ^= 1ULL << position;
                    newGame.game[color][Pawn] |= 1ULL << position + 16 - 32 * color;
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position + 16 - 32 * color, piece};
                        move.score = 0;
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                }
                if (((color == White && position/8 < 7) || (color == Black && position/8 > 0)) && !((1ULL << (position + 8 - 16 * color)) & AllBitBoard(Game))) {
                    if ((color == White && position/8 < 6) || (color == Black && position/8 > 1)) { 
                        newGame.game[color][Pawn] ^= 1ULL << position;
                        newGame.game[color][Pawn] |= 1ULL << (position + 8 - 16 * color);
                        if (!inCheck(&newGame, color)) {
                            struct Move move = {position, position + 8 - 16 * color, Pawn};
                            move.score = 0;
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            moves->moves[moves->count++] = move;
                        }
                        newGame = *Game;
                    }
                    else {
                        for (int k = Knight; k <= Queen; ++k) {
                            enum Piece t = (enum Piece)k;
                            newGame.game[color][Pawn] ^= 1ULL << position;
                            newGame.game[color][k] |= 1ULL << (position + 8 - 16*color);
                            if (!inCheck(&newGame, color)) {
                                struct Move move = {position, position + 8 - 16 * color, Pawn, t};
                                move.score = 0;
                                move.score += pieceValue[k];
                                if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                                else if (inCheck(&newGame, !color)) move.score += 200;
                                moves->moves[moves->count++] = move;
                            }
                        newGame = *Game;
                        }
                    }
                }
                if (((color == White && position/8 < 7) || (color == Black && position/8 > 0)) && position % 8 > 0 && ((1ULL << (position + 7 - 16 * color)) & ColorBitBoard(Game, !color))) {
                    if ((color == White && position/8 < 6) || (color == Black && position/8 > 1)) {
                        newGame.game[color][Pawn] ^= 1ULL << position;
                        newGame.game[color][Pawn] |= 1ULL << (position + 7 - 16 * color);
                        int x = CheckCollision(1ULL << (position + 7 - 16*color), Game, &newGame, !color);
                        if (!inCheck(&newGame, color)) {
                            struct Move move = {position, position + 7 - 16 * color, Pawn};
                            move.score = 0;
                            move.score += pieceValue[x-1] * 10 - pieceValue[Pawn];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            moves->moves[moves->count++] = move;
                        }
                        newGame = *Game;
                    }
                    else {
                        for (int k = Knight; k <= Queen; ++k) {
                            enum Piece t = (enum Piece)k;
                            newGame.game[color][Pawn] ^= 1ULL << position;
                            newGame.game[color][Pawn] |= 1ULL << (position + 7 - 16*color);
                            int x = CheckCollision(1ULL << (position + 7 - 16*color), Game, &newGame, !color);
                            if (!inCheck(&newGame, color)) {
                                struct Move move = {position, position + 7 - 16*color, Pawn, t};
                                move.score = 0;
                                move.score += pieceValue[x-1] * 10 - pieceValue[Pawn];
                                if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                                else if (inCheck(&newGame, !color)) move.score += 200;
                                move.score += pieceValue[k];
                                moves->moves[moves->count++] = move;
                            }
                            newGame = *Game;
                        }
                    }
                }
                if (((color == White && position/8 < 7) || (color == Black && position/8 > 0)) && position % 8 < 7 && ((1ULL << (position + 9 - 16 * color)) & ColorBitBoard(Game, !color))) {
                    if (position/8 < 6) {
                        newGame.game[color][Pawn] ^= 1ULL << position;
                        newGame.game[color][Pawn] |= 1ULL << (position + 9 - 16 * color);
                        int x = CheckCollision(1ULL << (position + 9 - 16 * color), Game, &newGame, !color);
                        if (!inCheck(&newGame, color)) {
                            struct Move move = {position, position + 9 - 16 * color, Pawn};
                            move.score = 0;
                            move.score += pieceValue[x-1] * 10 - pieceValue[Pawn];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            moves->moves[moves->count++] = move;
                        }
                        newGame = *Game;
                    }
                    else {
                        for (int k = Knight; k <= Queen; ++k) {
                            enum Piece t = (enum Piece)k;
                            newGame.game[color][Pawn] ^= 1ULL << position;
                            newGame.game[color][Pawn] |= 1ULL << (position + 9 - 16 * color);
                            int x = CheckCollision(1ULL << (position + 9 - 16 * color), Game, &newGame, !color);
                            if (!inCheck(&newGame, color)) {
                                struct Move move = {position, position + 9 - 16 * color, Pawn, t};
                                move.score = 0;
                                move.score += pieceValue[x-1] * 10 - pieceValue[Pawn];
                                if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                                else if (inCheck(&newGame, !color)) move.score += 200;
                                move.score += pieceValue[k];
                                moves->moves[moves->count++] = move;
                            }
                            newGame = *Game;

                        }
                    }
                }
            }
        }
        if (piece == Knight) {
            currentPiece = Game->game[color][Knight];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                if (position/8 < 7) {
                    if (position % 8 > 1 && !(ColorBitBoard(Game, color) & (1ULL << (position + 6)))) {
                        newGame.game[color][piece] ^= 1ULL << position;
                        newGame.game[color][piece] |= 1ULL << (position + 6);
                        int x = CheckCollision(1ULL << (position + 6), Game, &newGame, !color);
                        if (!inCheck(&newGame, color)) {
                            struct Move move = {position, position + 6, Knight};
                            move.score = 0;
                            if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            moves->moves[moves->count++] = move;
                        }
                        newGame = *Game;
                    }
                    if (position % 8 < 6 && !(ColorBitBoard(Game, color) & (1ULL << (position + 10)))) {
                        newGame.game[color][piece] ^= 1ULL << position;
                        newGame.game[color][piece] |= 1ULL << (position + 10);
                        int x = CheckCollision(1ULL << (position + 10), Game, &newGame, !color);
                        if (!inCheck(&newGame, color)) {
                            struct Move move = {position, position + 10, Knight};
                            move.score = 0;
                            if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            moves->moves[moves->count++] = move;
                        }
                        newGame = *Game;
                    }
                    if (position/8 < 6) {
                        if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position + 15)))) {
                            
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << (position + 15);
                            int x = CheckCollision(1ULL << (position + 15), Game, &newGame, !color);
                            if (!inCheck(&newGame, color)) {
                                struct Move move = {position , position + 15, Knight};
                                move.score = 0;
                                if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                                if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                                else if (inCheck(&newGame, !color)) move.score += 200;
                                moves->moves[moves->count++] = move;
                            }
                            newGame = *Game;
                        }
                        if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 17)))) {
                            
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << (position + 17);
                            int x = CheckCollision(1ULL << (position + 17), Game, &newGame, !color);
                            if (!inCheck(&newGame, color)) {
                                struct Move move = {position, position + 17, Knight};
                                move.score = 0;
                                if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                                if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                                else if (inCheck(&newGame, !color)) move.score += 200;
                                moves->moves[moves->count++] = move;
                            }
                            newGame = *Game;
                        }
                    }
                }
                if (position/8 > 0) {
                    if (position % 8 > 1 && !(ColorBitBoard(Game, color) & (1ULL << (position - 10)))) {

                        newGame.game[color][piece] ^= 1ULL << position;
                        newGame.game[color][piece] |= 1ULL << (position - 10);
                        int x = CheckCollision(1ULL << (position - 10), Game, &newGame, !color);
                        if (!inCheck(&newGame, color)) {
                            struct Move move = {position, position - 10, Knight};
                            move.score = 0;
                            if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            moves->moves[moves->count++] = move;
                        }
                        newGame = *Game;
                    }
                    if (position % 8 < 6 && !(ColorBitBoard(Game, color) & (1ULL << (position - 6)))) {
                        newGame.game[color][piece] ^= 1ULL << position;
                        newGame.game[color][piece] |= 1ULL << (position - 6);
                        int x = CheckCollision(1ULL << (position - 6), Game, &newGame, !color);
                        if (!inCheck(&newGame, color)) {
                            struct Move move = {position, position - 6, Knight};
                            move.score = 0;
                            if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                            if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                            else if (inCheck(&newGame, !color)) move.score += 200;
                            moves->moves[moves->count++] = move;
                        }
                        newGame = *Game;
                    }
                    if (position/8 > 1) {
                        if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 17)))) {
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << (position - 17);
                            int x = CheckCollision(1ULL << (position - 17), Game, &newGame, !color);
                            if (!inCheck(&newGame, color)) {
                                struct Move move = {position , position - 17, Knight};
                                move.score = 0;
                                if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                                if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                                else if (inCheck(&newGame, !color)) move.score += 200;
                                moves->moves[moves->count++] = move;
                            }
                            newGame = *Game;
                        }
                        if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position - 15)))) {
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << (position - 15);
                            int x = CheckCollision(1ULL << (position - 15), Game, &newGame, !color);
                            if (!inCheck(&newGame, color)) {
                                struct Move move = {position, position - 15, Knight};
                                move.score = 0;
                                if (x) move.score += pieceValue[x-1]*10 - pieceValue[piece];
                                if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                                else if (inCheck(&newGame, !color)) move.score += 200;
                                moves->moves[moves->count++] = move;
                            }
                            newGame = *Game;
                        }
                    }
                }
            }
        }
        if (piece == Rook || piece == Queen) {
            currentPiece = Game->game[color][Piece];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                for (int y = position/8 + 1; y <= 7; ++y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (position % 8 + 8*y))) break;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position % 8 + 8*y);
                    int z = CheckCollision(1ULL << (position % 8 + 8*y), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position % 8 + 8*y, piece};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                    if (ColorBitBoard(Game, !color) & (1ULL << (position % 8 + 8*y))) break;
                }
                for (int y = position/8 - 1; y >= 0; --y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (position % 8 + 8*y))) break;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position % 8 + 8*y);
                    int z = CheckCollision(1ULL << (position % 8 + 8*y), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position % 8 + 8*y, piece};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                    if (ColorBitBoard(Game, !color) & (1ULL << (position % 8 + 8*y))) break;
                }
                for (int x = position % 8 + 1; x <= 7; ++x) {
                    if (ColorBitBoard(Game, color) & (1ULL << ((position/8) *8 + x))) break;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << ((position/8) *8 + x);
                    int z = CheckCollision(1ULL << ((position/8) *8 + x), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, (position/8) *8 + x, piece};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                    if (ColorBitBoard(Game, !color) & (1ULL << ((position/8) *8 + x))) break;
                }
                for (int x = position % 8 -1; x >= 0; --x) {
                    if (ColorBitBoard(Game, color) & (1ULL << ((position/8) *8 + x))) break;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << ((position/8) *8 + x);
                    int z = CheckCollision(1ULL << ((position/8) *8 + x), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, (position/8) *8 + x, piece};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                    if (ColorBitBoard(Game, !color) & (1ULL << ((position/8) *8 + x))) break;
                }
            }
        }
        if (piece == Bishop || piece == Queen) {
            currentPiece = Game->game[color][piece];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                //top left
                for (int y = position/8 + 1, x = position % 8 + 1; x <= 7 && y <= 7; ++x, ++y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (8*y + x))) break;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (8*y + x);
                    int z = CheckCollision(1ULL << (8*y + x), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, 8*y + x, piece};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                    if (ColorBitBoard(Game, !color) & (1ULL << (8*y + x))) break;
                }
                //top right
                for (int y = position/8 + 1, x = position % 8 - 1; x >= 0 && y <= 7; --x, ++y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (8*y + x))) break;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (8*y + x);
                    int z = CheckCollision(1ULL << (8*y + x), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, 8*y + x, piece};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                    if (ColorBitBoard(Game, !color) & (1ULL << (8*y + x))) break;
                }
                //bottom right
                for (int y = position/8 -1, x = position % 8 - 1; x >= 0 && y >= 0; --x, --y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (8*y + x))) break;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (8*y + x);
                    int z = CheckCollision(1ULL << (8*y + x), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, 8*y + x, piece};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                    if (ColorBitBoard(Game, !color) & (1ULL << (8*y + x))) break;
                }
                //bottom left
                for (int y = position/8 - 1, x = position % 8 + 1; x <= 7 && y >= 0; ++x, --y) {
                    if (ColorBitBoard(Game, color) & (1ULL << (8*y + x))) break;
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (8*y + x);
                    int z = CheckCollision(1ULL << (8*y + x), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, 8*y + x, piece};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                    if (ColorBitBoard(Game, !color) & (1ULL << (8*y + x))) break;
                }
            }
        }
        if (piece == King) {
            long long unsigned int tempPiece = 0;
            position = __builtin_ctzll(Game->game[color][King]);
            if (position/8 < 7) {
                if (!(ColorBitBoard(Game, color) & (1ULL << (position + 8)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position + 8);
                    int z = CheckCollision(1ULL << (position + 8), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position + 8, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                }
                if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position + 7)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position + 7);
                    int z = CheckCollision(1ULL << (position + 7), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position + 7, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                }
                if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 9)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position + 9);
                    int z = CheckCollision(1ULL << (position + 9), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position + 9, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                }
            }
            if (position/8 > 0) {
                if (!(ColorBitBoard(Game, color) & (1ULL << (position - 8)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position - 8);
                    int z = CheckCollision(1ULL << (position - 8), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position - 8, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                }
                if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 9)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position -9);
                    int z = CheckCollision(1ULL << (position -9), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position -9, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                }
                if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position - 7)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position -7);
                    int z = CheckCollision(1ULL << (position -7), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position -7, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
                }
            }
            if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 1)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position -1);
                    int z = CheckCollision(1ULL << (position -1), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position -1, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
            }
            if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 1)))) {
                    newGame.game[color][piece] ^= 1ULL << position;
                    newGame.game[color][piece] |= 1ULL << (position +1);
                    int z = CheckCollision(1ULL << (position + 1), Game, &newGame, !color);
                    if (!inCheck(&newGame, color)) {
                        struct Move move = {position, position + 1, King};
                        move.score = 0;
                        if (z) move.score += pieceValue[z-1]*10 - pieceValue[piece];
                        if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                        else if (inCheck(&newGame, !color)) move.score += 200;
                        moves->moves[moves->count++] = move;
                    }
                    newGame = *Game;
            }
            //castle
            if (!inCheck(Game, color) && ((color == White && Game->WhiteCastle != Neither) || (color == Black && Game->BlackCastle != Neither))) {
                if (color == White) {
                    //check left castle
                    if (Game->WhiteCastle == WhiteBoth || Game->WhiteCastle == WhiteQueen) {
                        tempPiece = (1ULL << 4) | (1ULL << 5) | (1ULL << 6);
                        if (!(tempPiece & AllBitBoard(Game)) && !(isSquareAttacked(4, Game, White) || isSquareAttacked(5, Game, White)) || isSquareAttacked(6, Game, White)) {
                            newGame.game[color][piece] ^= 1ULL << 3;
                            newGame.game[color][piece] |= 1ULL << 5;
                            newGame.game[color][Rook] ^= 1ULL << 7;
                            newGame.game[color][Rook] |= 1ULL << 4;
                            if (!inCheck(&newGame, color)) {
                                struct Move move = {3, 5, King};
                                move.score = 100;
                                if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                                else if (inCheck(&newGame, !color)) move.score += 200;
                                moves->moves[moves->count++] = move;
                            }
                            newGame = *Game;
                        }
                    }
                    //check right castle
                    if (Game->WhiteCastle == WhiteBoth || Game->WhiteCastle == WhiteKing) {
                        tempPiece = (1ULL << 2) | (1ULL << 1);
                        if (!(tempPiece & AllBitBoard(Game)) && !(isSquareAttacked(2, Game, White) || isSquareAttacked(1, Game, White))){
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << 1;
                            newGame.game[color][Rook] ^= 1ULL;
                            newGame.game[color][Rook] |= 1ULL << 2;
                            if (!inCheck(&newGame, color)) {
                                struct Move move = {3, 1, King};
                                move.score = 100;
                                if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                                else if (inCheck(&newGame, !color)) move.score += 200;
                                moves->moves[moves->count++] = move;
                            }
                            newGame = *Game;
                        }
                    }
                }
                else if (color == Black) {
                    //check left castle
                    if (Game->BlackCastle == BlackBoth || Game->BlackCastle == BlackQueen) {
                        tempPiece = (1ULL << 62) | (1ULL << 61) | (1ULL << 60);
                        if (!(tempPiece & AllBitBoard(Game)) && !(isSquareAttacked(60, Game, Black) || isSquareAttacked(61, Game, Black))){
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << (61);
                            newGame.game[color][Rook] ^= 1ULL << 63;
                            newGame.game[color][Rook] |= 1ULL << 60;
                            if (!inCheck(&newGame, color)) {
                                struct Move move = {59, 61, King};
                                move.score = 100;
                                if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                                else if (inCheck(&newGame, !color)) move.score += 200;
                                moves->moves[moves->count++] = move;
                            }
                            newGame = *Game;
                        }
                    }
                    //check right castle
                    if (Game->BlackCastle == BlackBoth || Game->BlackCastle == BlackKing) {
                        tempPiece = (1ULL << 58) | (1ULL << 57);
                        if (!(tempPiece & AllBitBoard(Game)) && !(isSquareAttacked(58, Game, Black) || isSquareAttacked(57, Game, Black))){
                            newGame.game[color][piece] ^= 1ULL << position;
                            newGame.game[color][piece] |= 1ULL << 57;
                            newGame.game[color][Rook] ^= 1ULL << 56;
                            newGame.game[color][Rook] |= 1ULL << 58;
                            if (!inCheck(&newGame, color)) {
                                struct Move move = {59, 57, King};
                                move.score = 100;
                                if (gameOver(!color, &newGame) == Checkmate) move.score += 1000000;
                                else if (inCheck(&newGame, !color)) move.score += 200;
                                moves->moves[moves->count++] = move;
                            }
                            newGame = *Game;
                        }
                    }
                }                    
            }
        }
    }
}

int inCheck(struct gameBoard *Game, enum Color turn) {
    return isSquareAttacked(__builtin_ctzll(Game->game[turn][King]), Game, turn);
}

int isSquareAttacked(int position, struct gameBoard *Game, enum Color turn) //check if "turn" color is in check
{    
    //check for pawn attacks
    if (turn == White){
        if (position/8 < 7){
            long long int PossiblePawn = 0b0ULL;
            if (position % 8 > 0) PossiblePawn |= (1ULL << 7 + position);
            if (position % 8 < 7) PossiblePawn |= (1ULL << 9 + position);
            if (PossiblePawn & Game->game[!turn][Pawn]) return 1;
        }
    }
    else {
        if (position/8 > 0){
            long long int PossiblePawn = 0b0ULL;
            if (position % 8 > 0) PossiblePawn |= (1ULL << position - 9);
            if (position % 8 < 7) PossiblePawn |= (1ULL << position - 7);
            if (PossiblePawn & Game->game[!turn][Pawn]) return 1;
        }
    }
    
    //check for knight attakcs
    if (position/8 < 7) {
        long long int possibleKnight = 0b0ULL;
        if (position % 8 < 6) possibleKnight |= (1ULL << position + 10);
        if (position % 8 > 1) possibleKnight |= (1ULL << position + 6);
        if (position/8 < 6) {
            
            if (position % 8 > 0) possibleKnight |= (1ULL << position + 15);
            
            if (position % 8 < 7) possibleKnight |= (1ULL << position + 17);
        }
        if (possibleKnight & Game->game[!turn][Knight]) return 1;
    }
    if (position/8 > 0) {
        long long int possibleKnight = 0b0ULL;
        if (position % 8 > 1) possibleKnight |= (1ULL << position - 10);
        if (position % 8 < 6) possibleKnight |= (1ULL << position - 6);
        if (position/8 > 1){
            if (position % 8 > 0) possibleKnight |= (1ULL << position - 17);
            if (position % 8 < 7) possibleKnight |= (1ULL << position - 15);
        }
        if (possibleKnight & Game->game[!turn][Knight]) return 1;
    }
    //king attacks
    if (position/8 < 7) {
        if ((1ULL << (position + 8)) & Game->game[!turn][King]) return 1;
        if (position%8 < 7) {
            if ((1ULL << (position + 9)) & Game->game[!turn][King]) return 1;
        }
        if (position%8 > 0) {
            if ((1ULL << (position + 7)) & Game->game[!turn][King]) return 1;
        }
    }
    if (position/8 > 0) {
        if ((1ULL << (position - 8)) & Game->game[!turn][King]) return 1;
        if (position%8 < 7) {
            if ((1ULL << (position - 7)) & Game->game[!turn][King]) return 1;
        }
        if (position%8 > 0) {
            if ((1ULL << (position - 9)) & Game->game[!turn][King]) return 1;
        }
    }
    if (position % 8 > 0) {
        if ((1ULL << (position - 1)) & Game->game[!turn][King]) return 1;
    }
    if (position % 8 < 7) {
        if ((1ULL << (position + 1)) & Game->game[!turn][King]) return 1;
    }
    //Check Vertical Up

    for (int current = position + 8; (current - 8)/8 < 7; current += 8) {
        long long unsigned int temp = 1ULL << current;
        if ((temp & Game->game[!turn][Rook]) | (temp & Game->game[!turn][Queen])) return 1;
        if (temp & AllBitBoard(Game)) break;
    }
    //Check Vertival Down - Problem
    for (int current = position - 8; (current + 8)/8 > 0; current -= 8) {
        long long unsigned int temp = 1ULL << current;
        if ((temp & Game->game[!turn][Rook]) | (temp & Game->game[!turn][Queen])) return 1;
        if (temp & AllBitBoard(Game)) break;
    }
    
    //Check Horizontal Left
    for (int current = position + 1; (current - 1) % 8 < 7; current += 1) {
        long long unsigned int temp = 1ULL << current;
        if ((temp & Game->game[!turn][Rook]) | (temp & Game->game[!turn][Queen])) return 1;
        if (temp & AllBitBoard(Game)) break;
    }

    //Check Horizontal Right
    for (int current = position - 1; (current + 1) % 8 > 0; current -= 1) {
        long long unsigned int temp = 1ULL << current;
        if ((temp & Game->game[!turn][Rook]) | (temp & Game->game[!turn][Queen])) return 1;
        if (temp & AllBitBoard(Game)) break;
    }

    //Check Diagonal Top left
    for (int current = position + 9; (current - 9) % 8 < 7 && (current - 9)/8 < 7; current += 9){
        long long unsigned int temp = 1ULL << current;
        if ((Game->game[!turn][Bishop] | Game->game[!turn][Queen]) & temp) return 1;
        if (temp & AllBitBoard(Game)) break;
    }

    //Check Diagonal Top Right
    for (int current = position + 7; (current - 7) %8 > 0 && (current - 7)/8 < 7; current += 7) {
        long long unsigned int temp = 1ULL << current;
        if ((Game->game[!turn][Bishop] | Game->game[!turn][Queen]) & temp) return 1;
        if (temp & AllBitBoard(Game)) break; 
    }

    //Check Diagonal Bottom Left
    for (int current = position - 7; (current + 7) %8 < 7 && (current + 7)/8 > 0; current -= 7) {
        long long unsigned int temp = 1ULL << current;
        if ((Game->game[!turn][Bishop] | Game->game[!turn][Queen]) & temp) return 1;
        if (temp & AllBitBoard(Game)) break; 
    }

    //Check Diagonal Bottom Right
    for (int current = position - 9; (current + 9) %8 > 0 && (current + 9)/8 > 0; current -= 9) {
        long long unsigned int temp = 1ULL << current;
        if ((Game->game[!turn][Bishop] | Game->game[!turn][Queen]) & temp) return 1;
        if (temp & AllBitBoard(Game)) break; 
    }
    return 0;    
}

int Phase(struct gameBoard *Game) {
    return min(4 *  __builtin_popcountll(Game->game[White][Queen] | Game->game[Black][Queen]) +
        __builtin_popcountll(Game->game[White][Knight] | Game->game[Black][Knight] | Game->game[White][Bishop] | Game->game[Black][Bishop]) +
        __builtin_popcountll(Game->game[White][Rook] | Game->game[Black][Rook]) * 2 , 24);
}

int evaluate(struct gameBoard *Game, enum Color turn) {
    int phase = Phase(Game);
    //return (evaluateBoard(Game, mgPst));
    return (evaluateBoard(Game, mgPst) * phase + evaluateBoard(Game, egPst) * (24 - phase))/24;
}

int evaluateBoard(struct gameBoard *Game, int **Pst){    
    int score = 0;
    int coord;
    unsigned long long int current;
    
    for (int Piece = Queen; Piece >= King; --Piece) {
        enum Piece piece = (enum Piece)Piece;
        current = Game->game[White][piece];
        while (current) {
            coord = __builtin_ctzll(current);
            current &= current - 1;
            score = score + pieceValue[piece] + Pst[piece][coord];
        }
        current = Game->game[Black][piece];
        while (current) {
            coord = __builtin_ctzll(current);
            current &= current - 1;
            score = score - pieceValue[piece] - Pst[piece][63 - coord];
        }
    }
    return score;
}


//check if color side still has legal moves -> used to determine end of game
int MoreMoves(struct gameBoard *Game, enum Color color) {
    int position = 0;
    long long int currentPiece = 0;
    long long int tempPiece = 0;
    struct gameBoard copyGame = *Game;
    int reset = 0;
    for (int Piece = Queen; Piece >= King; --Piece){
        enum Piece piece = (enum Piece)Piece;
        if (piece == Pawn) {
            if (color == White) {
                currentPiece = Game->game[color][piece];
                while (currentPiece){
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    if (position/8 == 1 && !(((1ULL << (position + 8)) | (1ULL << (position + 16))) & AllBitBoard(Game))) { //pawn move 2 forward
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position + 16) - (1ULL << position);
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        copyGame.game[color][piece] = tempPiece;
                    }
                    if (position/8 < 7 && !((1ULL << (position + 8)) & AllBitBoard(Game))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position + 8) - (1ULL << position);
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        copyGame.game[color][piece] = tempPiece;
                    }
                    if (position/8 < 7 && position % 8 > 0 && ((1ULL << (position + 9)) & ColorBitBoard(Game, !color))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position + 9) - (1ULL << position);
                        if (CheckCollision(1ULL << (position + 9), Game, &copyGame, !color)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][piece] = tempPiece;
                        }
                    }
                    if (position/8 < 7 && position % 8 < 7 && ((1ULL << (position + 7)) & ColorBitBoard(Game, !color))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position + 7) - (1ULL << position);
                        if (CheckCollision(1ULL << (position + 7), Game, &copyGame, !color)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][piece] = tempPiece;
                        }
                    }
                    if (copyGame.enPassant[Black] < 8 && position/8 == 4) {
                        if (abs(copyGame.enPassant[Black] - position%8) == 1) {
                            copyGame.game[Black][Pawn] ^= 1ULL << 32 + copyGame.enPassant[Black];
                            copyGame.game[White][Pawn] ^= 1ULL << position;
                            copyGame.game[White][Pawn] |= 40 + copyGame.enPassant[Black];
                            copyGame.enPassant[Black] = 8;
                            if (!inCheck(&copyGame, color)) return 1;
                            //can shorten this copy for optimization
                            copyGame = *Game;
                            
                        }
                    }
                }
            }
            else {
                currentPiece = Game->game[color][piece];
                while (currentPiece) {
                    position = __builtin_ctzll(currentPiece);
                    currentPiece &= currentPiece - 1;
                    if (position/8 == 6 && !(((1ULL << (position - 8)) | (1ULL << (position - 16))) & AllBitBoard(Game))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position - 16) - (1ULL << position);
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        copyGame.game[color][piece] = tempPiece;
                    }
                    if (position/8 > 0 && !((1ULL << (position - 8)) & AllBitBoard(Game))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position - 8) - (1ULL << position);
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        copyGame.game[color][piece] = tempPiece;
                    }
                    if (position/8 > 0 && position % 8 > 0 && ((1ULL << position - 9) & ColorBitBoard(Game, !color))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position - 9) - (1ULL << position);
                        if (CheckCollision(1ULL << (position - 9), Game, &copyGame, !color)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][piece] = tempPiece;
                        }
                    }
                    if (position/8 > 0 && position % 8 < 7 && ((1ULL << (position - 7) & ColorBitBoard(Game, !color)))) {
                        tempPiece = Game->game[color][piece];
                        copyGame.game[color][piece] += (1ULL << position - 7) - (1ULL << position);
                        if (CheckCollision(1ULL << (position - 7), Game, &copyGame, !color)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][piece] = tempPiece;
                        }
                    }
                    if (copyGame.enPassant[White] < 8 && position/8 == 3) {
                        if (abs(copyGame.enPassant[Black] - position%8) == 1) {
                            copyGame.game[White][Pawn] ^= 1ULL << 24 + copyGame.enPassant[White];
                            copyGame.game[Black][Pawn] ^= 1ULL << position;
                            copyGame.game[Black][Pawn] |= 32 + copyGame.enPassant[White];
                            copyGame.enPassant[White] = 8;
                            if (!inCheck(&copyGame, color)) return 1;
                            //can shorten this copy for optimization
                            copyGame = *Game;
                            
                        }
                    }
                }
            }
        }
        if (piece == Knight) {
            currentPiece = Game->game[color][Knight];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                if (position/8 < 7) {
                    if (position % 8 > 1 && !(ColorBitBoard(Game, color) & (1ULL << (position + 6)))) {
                        tempPiece = Game->game[color][Knight];
                        copyGame.game[color][piece] += (1ULL << position + 6) - (1ULL << position);
                        if (CheckCollision(1ULL << (position + 6), Game, &copyGame, !color)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][Knight] = tempPiece;
                        }
                    }
                    if (position % 8 < 6 && !(ColorBitBoard(Game, color) & (1ULL << (position + 10)))) {
                        tempPiece = Game->game[color][Knight];
                        copyGame.game[color][piece] += (1ULL << position + 10) - (1ULL << position);
                        if (CheckCollision(1ULL << (position + 10), Game, &copyGame, !color)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][Knight] = tempPiece;
                        }
                    }
                    if (position/8 < 6) {
                        if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position + 15)))) {
                            tempPiece = Game->game[color][Knight];
                            copyGame.game[color][piece] += (1ULL << position + 15) - (1ULL << position);
                            if (CheckCollision(1ULL << (position + 15), Game, &copyGame, !color)) reset = 1;
                            if (!inCheck(&copyGame, color)) {
                                return 1;
                            }
                            if (reset) {
                                copyGame = *Game;
                                reset = 0;
                            }
                            else {
                                copyGame.game[color][Knight] = tempPiece;
                            }
                        }
                        if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 17)))) {
                            tempPiece = Game->game[color][Knight];
                            copyGame.game[color][piece] += (1ULL << position + 17) - (1ULL << position);
                            if (CheckCollision(1ULL << (position + 17), Game, &copyGame, !color)) reset = 1;
                            if (!inCheck(&copyGame, color)) {
                                return 1;
                            }
                            if (reset) {
                                copyGame = *Game;
                                reset = 0;
                            }
                            else {
                                copyGame.game[color][Knight] = tempPiece;
                            }
                        }
                    }
                }
                if (position/8 > 0) {
                    if (position % 8 > 1 && !(ColorBitBoard(Game, color) & (1ULL << (position - 10)))) {
                        tempPiece = Game->game[color][Knight];
                        copyGame.game[color][piece] += (1ULL << position - 10) - (1ULL << position);
                        if (CheckCollision(1ULL << (position - 10), Game, &copyGame, !color)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][Knight] = tempPiece;
                        }
                    }
                    if (position % 8 < 6 && !(ColorBitBoard(Game, color) & (1ULL << (position - 6)))) {
                        tempPiece = Game->game[color][Knight];
                        copyGame.game[color][piece] += (1ULL << position - 6) - (1ULL << position);
                        if (CheckCollision(1ULL << (position - 6), Game, &copyGame, !color)) reset = 1;
                        if (!inCheck(&copyGame, color)) {
                            return 1;
                        }
                        if (reset) {
                            copyGame = *Game;
                            reset = 0;
                        }
                        else {
                            copyGame.game[color][Knight] = tempPiece;
                        }
                    }
                    if (position/8 > 1) {
                        if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 17)))) {
                            tempPiece = Game->game[color][Knight];
                            copyGame.game[color][piece] += (1ULL << position - 17) - (1ULL << position);
                            if (CheckCollision(1ULL << (position - 17), Game, &copyGame, !color)) reset = 1;
                            if (!inCheck(&copyGame, color)) {
                                return 1;
                            }
                            if (reset) {
                                copyGame = *Game;
                                reset = 0;
                            }
                            else {
                                copyGame.game[color][Knight] = tempPiece;
                            }
                        }
                        if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position - 15)))) {
                            tempPiece = Game->game[color][Knight];
                            copyGame.game[color][piece] += (1ULL << position - 15) - (1ULL << position);
                            if (CheckCollision(1ULL << (position - 15), Game, &copyGame, !color)) reset = 1;
                            if (!inCheck(&copyGame, color)) {
                                return 1;
                            }
                            if (reset) {
                                copyGame = *Game;
                                reset = 0;
                            }
                            else {
                                copyGame.game[color][Knight] = tempPiece;
                            }
                        }
                    }
                }
            }
        }
        if (piece == Rook || piece == Queen) {
            currentPiece = Game->game[color][Piece];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                for (int x = position % 8,  y = position/8 + 1; y <= 7 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); ++y) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame, !color);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
                for (int x = position % 8,  y = position/8 - 1; y >= 0 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); --y) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame, !color);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
                for (int x = position % 8 - 1, y = position/8; x >= 0 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); --x) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame, !color);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
                for (int x = position % 8 + 1, y = position/8; x <= 7 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); --x) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame, !color);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
            }
        }
        if (piece == Bishop || piece == Queen) {
            currentPiece = Game->game[color][piece];
            while (currentPiece) {
                position = __builtin_ctzll(currentPiece);
                currentPiece &= currentPiece - 1;
                for (int x = position % 8 + 1,  y = position/8 + 1; y <= 7 && x <= 7 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); ++y, ++x) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame, !color);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
                for (int x = position % 8 - 1,  y = position/8 + 1; y <= 7 && x >= 0 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); ++y, --x) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame, !color);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
                for (int x = position % 8 - 1,  y = position/8 - 1; y >= 0 && x >= 0 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); --y, --x) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame, !color);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
                for (int x = position % 8 + 1,  y = position/8 - 1; y >= 0 && x <= 7 && !(ColorBitBoard(Game, color) & (1ULL << (8*y + x))); --y, ++x) {
                    copyGame.game[color][piece] += (1ULL << 8*y + x) - (1ULL << position);
                    int t = CheckCollision(1ULL << (8*y + x), Game, &copyGame, !color);
                    if (!inCheck(&copyGame, color)) return 1;
                    copyGame = *Game;
                    if (t) break;
                }
            }
        }
        if (piece == King) {
            position = __builtin_ctzll(Game->game[color][King]);
            if (position/8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 8)))) {
                copyGame.game[color][piece] += (1ULL << position + 8) - (1ULL << position);
                CheckCollision(1ULL << (position + 8), Game, &copyGame, !color);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position/8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 8)))){
                copyGame.game[color][piece] += (1ULL << position - 8) - (1ULL << position);
                CheckCollision(1ULL << (position - 8), Game, &copyGame, !color);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 1)))){
                copyGame.game[color][piece] += (1ULL << position - 1) - (1ULL << position);
                CheckCollision(1ULL << (position - 1), Game, &copyGame, !color);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 1)))){     
                copyGame.game[color][piece] += (1ULL << position + 1) - (1ULL << position);
                CheckCollision(1ULL << (position + 1), Game, &copyGame, !color);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position/8 < 7 && position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position + 9)))){
                copyGame.game[color][piece] += (1ULL << position + 9) - (1ULL << position);
                CheckCollision(1ULL << (position + 9), Game, &copyGame, !color);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position/8 < 7 && position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position + 7)))){
                copyGame.game[color][piece] += (1ULL << position + 7) - (1ULL << position);
                CheckCollision(1ULL << (position + 7), Game, &copyGame, !color);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position/8 > 0 && position % 8 > 0 && !(ColorBitBoard(Game, color) & (1ULL << (position - 9)))){
                copyGame.game[color][piece] += (1ULL << position - 9) - (1ULL << position);
                CheckCollision(1ULL << (position - 9), Game, &copyGame, !color);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
            if (position/8 > 0 && position % 8 < 7 && !(ColorBitBoard(Game, color) & (1ULL << (position - 7)))){
                copyGame.game[color][piece] += (1ULL << position - 7) - (1ULL << position);
                CheckCollision(1ULL << (position - 7), Game, &copyGame, !color);
                if (!inCheck(&copyGame, color)) return 1;
                copyGame = *Game;
            }
        }
    }
    return 0;
}

int gameOver (enum Color turn, struct gameBoard *game) //check if "turn" color lost
{
    if (MoreMoves(game, turn)) return Play;
    if (inCheck(game, turn)) return Checkmate;
    return Stalemate;
}
int Nodes = 0;
int get_Nodes() {
    return Nodes;
}
void set_Nodes(int i) {
    Nodes = i;
}
//ASSUME ITS WHITE PLAYING AS MAXIMIZING
int alphabeta(int depth, struct gameBoard *Game, int alpha, int beta, int maximizingPlayer, struct Move *Move, struct TTEntry *table, struct Stack *stack) {
    Nodes += 1;
    unsigned long long int hash = computeHash(Game, !maximizingPlayer);
    int x = gameOver(!maximizingPlayer, Game);
    if (search(stack, hash) >= 2) return 0;
    if (x == Stalemate) return 0;
    else if (x == Checkmate) {
        if (maximizingPlayer) return -INF + (DEPTH - depth);
        else {
            return INF - (DEPTH - depth);
        }
    }

    if (depth == 0) return evaluate(Game, !maximizingPlayer);

    struct TTEntry *entry = probe(hash, table);
    
    if (entry && entry->depth >= depth) {
        if (entry->flag == EXACT) {
            if (depth == DEPTH) *Move = entry->BestMove;
            return entry->score;
        }
        if (entry->flag == LOWERBOUND && entry->score >= beta) {
            if (depth == DEPTH) *Move = entry->BestMove;
            return entry->score;
        }
        if (entry->flag == HIGHERBOUND && entry->score <= alpha) {
            if (depth == DEPTH) *Move = entry->BestMove;
            return entry->score;
        }
    }
    struct Move BestMove;
    int eval;
    int originalAlpha = alpha, originalBeta = beta;

    struct MoveList moves;
    generateMoves(Game, &moves, !maximizingPlayer);
    InsertSort(moves.moves, moves.count);
    
    //Maximizing Player
    if (maximizingPlayer) {
        int maxEval = -INF;
        struct Move move;
        struct gameBoard newGame;
        for (int i = 0; i < moves.count; ++i) {
            newGame = *Game;

            move = moves.moves[i];
            //apply move
            
            newGame.game[White][move.piece] ^= (1ULL << move.start);
            newGame.game[White][move.piece] |= (1ULL << move.end);

            int captured = CheckCollision((1ULL << move.end), &newGame, &newGame, maximizingPlayer);            
            //if we captured a rook
            if (captured - 1 == Rook) {
                if (move.end == 56) {
                    if (Game->BlackCastle == BlackBoth) newGame.BlackCastle = BlackQueen;
                    else newGame.BlackCastle = Neither;
                }
                else if (move.end == 63) {
                    if (Game->BlackCastle == WhiteBoth) newGame.BlackCastle = BlackKing;
                    else newGame.BlackCastle = Neither; 
                }
            }

            //check for promotion
            if (move.piece == Pawn && (move.end/8 == 7)) {
                newGame.game[White][Pawn] ^= (1ULL << move.end);
                newGame.game[White][move.promotion] |= (1ULL << move.end);
            }
            
            
            //check for castle
            if (move.piece == King && abs(move.start - move.end) == 2) {
                newGame.WhiteCastle = Neither;
                if (move.end == 5) {
                    newGame.game[White][Rook] ^= (1ULL << 7);
                    newGame.game[White][Rook] |= (1ULL << 4);
                }
                else {
                    newGame.game[White][Rook] ^= (1ULL);
                    newGame.game[White][Rook] |= (1ULL << 2);
                }  
            }
            else if (move.piece == King) newGame.WhiteCastle = Neither;
            
            //update castle status for rook move 
            if (move.piece == Rook && Game->WhiteCastle != Neither) {
                if (move.start == 0) {
                    if (Game->WhiteCastle == WhiteBoth) newGame.WhiteCastle = WhiteQueen;
                    else newGame.WhiteCastle = Neither;
                }
                else if (move.start == 7) {
                    if (Game->WhiteCastle == WhiteBoth) newGame.WhiteCastle = WhiteKing;
                    else newGame.WhiteCastle = Neither;
                }
            }

            //en passant
            if (Game->enPassant[Black] < 8 && move.start/8 == 4 && move.end % 8 == Game->enPassant[Black] && move.piece == Pawn) {
                newGame.game[Black][Pawn] ^= 1ULL << move.end - 8;
            }

            //reset enPassant
            newGame.enPassant[Black] = 8;

            //check for new enPassant flag
            if (move.piece == Pawn && abs(move.end - move.start) == 16){
                newGame.enPassant[White] = move.end % 8;
            }

            push(stack, computeHash(&newGame, Black));
            
            eval = alphabeta(depth-1, &newGame, alpha, beta, 0, Move, table, stack);

            pop(stack);


            if (eval > maxEval) {
                maxEval = eval;
                BestMove = move;
                if (depth == DEPTH) *Move = move;
            }
            alpha = max(alpha, eval);
            if (beta <= alpha) break;
        }

        int flag;
        if (maxEval <= originalAlpha) flag = HIGHERBOUND;
        else if (maxEval >= originalBeta) flag = LOWERBOUND;
        else flag = EXACT;
        store(hash, depth, maxEval, flag, BestMove, table);
        return maxEval;
    }
    else {
        int minEval = INF;
        struct Move move;
        struct gameBoard newGame;
        for (int i = 0; i < moves.count; ++i){
            newGame = *Game;
            move = moves.moves[i];

            newGame.game[Black][move.piece] ^= (1ULL << move.start);
            newGame.game[Black][move.piece] |= (1ULL << move.end);
            
            //if we captured a rook
            if (CheckCollision((1ULL << move.end), &newGame, &newGame, maximizingPlayer) - 1 == Rook) {
                if (move.end == 7) {
                    if (Game->WhiteCastle == WhiteBoth) newGame.WhiteCastle = WhiteKing;
                    else newGame.WhiteCastle = Neither;
                }
                if (move.end == 0) {
                    if (Game->WhiteCastle == WhiteBoth) newGame.WhiteCastle = WhiteQueen;
                    else newGame.WhiteCastle = Neither; 
                }
            }
            
            //Check promotion
            if (move.piece == Pawn && (move.end/8 == 0)) {
                newGame.game[Black][Pawn] ^= (1ULL << move.end);
                newGame.game[Black][move.promotion] |= (1ULL << move.end);
            }
            //check for castle
            if (move.piece == King && abs(move.start - move.end) == 2) {     
                newGame.BlackCastle = Neither;
                if (move.end == 61) {
                    newGame.game[Black][Rook] ^= (1ULL << 63);
                    newGame.game[Black][Rook] |= (1ULL << 60);
                }
                else {
                    newGame.game[Black][Rook] ^= (1ULL << 56);
                    newGame.game[Black][Rook] |= (1ULL << 58);
                }
            }
            else if (move.piece == King) newGame.BlackCastle = Neither;
        
            if (move.piece == Rook && Game->BlackCastle != Neither) {
                if (move.start == 63) {
                    if (Game->BlackCastle == BlackBoth) newGame.BlackCastle = BlackKing;
                    else newGame.BlackCastle = Neither;
                }
                else if (move.start == 56) {
                    if (Game->BlackCastle == BlackBoth) newGame.BlackCastle = BlackQueen;
                    else newGame.BlackCastle = Neither;
                } 
            }
            
            //en passant
            if (Game->enPassant[White] < 8 && move.start/8 == 3 && move.end % 8 == Game->enPassant[White] && move.piece == Pawn) {
                newGame.game[White][Pawn] ^= 1ULL << move.end + 8;
            }
            newGame.enPassant[White] = 8;


            if (move.piece == Pawn && abs(move.end - move.start) == 16){
                newGame.enPassant[Black] = move.end % 8;
            }

            push(stack, computeHash(&newGame, White));
            
            eval = alphabeta(depth-1, &newGame, alpha, beta, 1, Move, table, stack);
            
            pop(stack);


            if (eval < minEval) {
                minEval = eval;
                BestMove = move;
                if (depth == DEPTH) *Move = move;
            }
            beta = min(beta, eval);
            if (beta <= alpha) break;
        }

        int flag;
        if (minEval <= originalAlpha) flag = HIGHERBOUND;
        else if (minEval >= originalBeta) flag = LOWERBOUND;
        else flag = EXACT;
        store(hash, depth, minEval, flag, BestMove, table);
        return minEval;
    }
}